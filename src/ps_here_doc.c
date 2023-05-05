#include "../inc/execution.h"
#include "../inc/minishell.h"

void	fils_here_doc(char *limiter, int *fd);

void	ps_here_doc(char *limiter)
{
	int		fd[2];
	int		pid;

	if (pipe(fd) == -1)
		return ;
	pid = fork();
	if (pid == -1)
		perror("An error as occured while attempting to fork");
	if (pid == 0)
		fils_here_doc(limiter, fd);
	else
	{
		close(fd[1]);
		dup2(fd[0], STDIN_FILENO);
		close(fd[0]);
		waitpid(-1, NULL, 0);
	}
}

void	fils_here_doc(char *limiter, int *fd)
{
	char	*next_line;

	close (fd[0]);
	write(1, "pipe heredoc>", 13);
	while (1)
	{
		next_line = get_next_line(STDIN_FILENO);
		if (!next_line || f_strcmp(next_line, limiter) == 0)
		{
			free(next_line);
			close (fd[1]);
			break ;
		}
		write(1, "pipe heredoc>", 13);
		write(fd[1], next_line, f_strlen(next_line));
		write(fd[1], "\n", 1);
		free(next_line);
	}
	free(limiter);
	close (fd[1]);
	exit(0);
}

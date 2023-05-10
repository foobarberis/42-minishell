#include "../inc/minishell.h"
#include "../inc/minishell.h"

void	fils_here_doc(char *limiter, int *fd);

int	ps_here_doc(char *limiter)
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
	return (3);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	i;
	size_t	j;
	size_t	size_tot;
	char	*res;

	i = -1;
	j = 0;
	if (!s1 && !s2)
		return (NULL);
	if (!s2)
		return ((char *)s1);
	if (!s1)
		return ((char *)s2);
	size_tot = f_strlen((char *)s1) + f_strlen((char *)s2);
	if (size_tot >= SIZE_MAX)
		return (NULL);
	res = malloc(sizeof(char) * (size_tot + 1));
	if (!res)
		return (NULL);
	while (s1[++i])
		res[i] = s1[i];
	while (s2[j])
		res[i++] = s2[j++];
	res[i] = '\0';
	return (res);
}

void	fils_here_doc(char *limiter, int *fd)
{
	char	*next_line;
	char	*line;
	char	*buffer;

	line = NULL;
	buffer = NULL;
	close (fd[0]);
	while (1)
	{
		next_line = readline(">");
		if (!next_line || f_strcmp(next_line, limiter) == 0)
		{
			free(next_line);
			close (fd[1]);
			break ;
		}
		if (line)
			buffer = f_strdup(line);
		dprintf(2,"next_line = %s et line = %s\n", next_line, line);
		free(line);
		line = ft_strjoin(buffer, next_line);
		free(next_line);
		free(buffer);
	}
	write(fd[1], line, f_strlen(line));
	free(limiter);
	close (fd[1]);
	exit(0);
}

// void	fils_here_doc(char *limiter, int *fd)
// {
// 	char	*next_line;
// 	char	*line;
// 	char	*buffer;

// 	close (fd[0]);
// 	line = NULL;
// 	buffer = NULL;
// 	write(1, "pipe heredoc>", 13);
// 	while (1)
// 	{
// 		next_line = get_next_line(STDIN_FILENO);
// 		dprintf(2,"NL = %s\n", next_line);
// 		if (next_line && f_strcmp(next_line, limiter) == 0)
// 		{
// 			free(next_line);
// 			close (fd[1]);
// 			break ;
// 		}
// 		write(1, "pipe heredoc>", 13);
// 		buffer = f_strdup(line);
// 		free(line);
// 		line = f_strjoin(buffer, next_line);
// 		free(next_line);
// 		free(buffer);
// 	}
// 	write(fd[1], line, f_strlen(line));
// 	free(line);
// 	free(limiter);
// 	close (fd[1]);
// 	exit(0);
// }
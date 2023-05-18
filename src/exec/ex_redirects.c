#include "../../inc/minishell.h"

void	nothing_to_redirect(t_cmd *cmd, size_t i, size_t nb_cmd)
{
	if (i > 0 && cmd[i].is_builtin == 0)
		dup2(cmd[i - 1].fd[0], STDIN_FILENO);
	if (i < nb_cmd - 1)
		dup2(cmd[i].fd[1], STDOUT_FILENO);
}

void	in_out_redirect(t_cmd *cmd, size_t i)
{
	size_t	len;

	if (cmd[i].is_here_doc)
	{
//		if (cmd[i].expand_here_doc == 1)
//			here_doc_expand_variable(cmd[i].string_here_doc);
		len = f_strlen(cmd[i].string_here_doc);
		write(cmd[i].fd[1], cmd[i].string_here_doc, len);
		dup2(cmd[i].fd[0], STDIN_FILENO);
	}
	else
	{
		dup2(cmd[i].final_input, STDIN_FILENO);
		close (cmd[i].final_input);
	}
	dup2(cmd[i].final_output, STDOUT_FILENO);
	close(cmd[i].final_output);
}

void	in_redirect(t_cmd *cmd, size_t i, size_t nb_cmd)
{
	size_t	len;

	if (cmd[i].is_here_doc)
	{
		len = f_strlen(cmd[i].string_here_doc);
		write(cmd[i].fd[1], cmd[i].string_here_doc, len);
		close(cmd[i].fd[1]);
		dup2(cmd[i].fd[0], STDIN_FILENO);
	}
	else
	{
		dup2(cmd[i].final_input, STDIN_FILENO);
		close (cmd[i].final_input);
	}
	if (i < nb_cmd - 1)
		dup2(cmd[i].fd[1], STDOUT_FILENO);
}

void	out_redirect(t_cmd *cmd, size_t i)
{
	if (i > 0)
		dup2(cmd[i - 1].fd[0], STDIN_FILENO);
	dup2(cmd[i].final_output, STDOUT_FILENO);
	close (cmd[i].final_output);
}

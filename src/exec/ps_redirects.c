/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ps_redirects.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vburton <vburton@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/30 14:15:21 by vburton           #+#    #+#             */
/*   Updated: 2023/05/30 14:15:22 by vburton          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	open_input(t_cmd *files)
{
	int	valid;

	if (files->type_in == S_INPUT)
		valid = open(files->input, O_RDONLY);
	else
	{
		files->is_here_doc = 1;
		valid = 0;
	}
	if (valid < SUCCESS)
	{
		files->is_valid = ERROR;
		perror(files->input);
		return (ERROR_REDIRECT);
	}
	return (valid);
}

int	open_output(t_cmd *files)
{
	int	valid;

	if (files->type_out == S_OUTPUT)
		valid = open(files->output, O_WRONLY | O_TRUNC | O_CREAT, 0644);
	else
		valid = open(files->output, O_WRONLY | O_APPEND | O_CREAT, 0644);
	if (valid < SUCCESS)
	{
		files->is_valid = ERROR;
		perror(files->output);
		return (ERROR_REDIRECT);
	}
	return (valid);
}

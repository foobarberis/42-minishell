/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_unset.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vburton <vburton@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/23 15:52:48 by mbarberi          #+#    #+#             */
/*   Updated: 2023/06/19 15:33:53 by vburton          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	blt_export(t_glb *glb, int argc, char **argv)
{
	size_t	i;

	i = 1;
	g_rval = 0;
	if (argc == 1)
		return (blt_export__print(glb));
	while (argv[i])
	{
		if (!env_is_valid_id(argv[i]))
		{
			g_rval = 1;
			f_dprintf(STDERR_FILENO,
				"minishell: export: `%s': not a valid identifier\n", argv[i++]);
		}
		else
		{
			glb->env = env_key_add(glb->env, f_strdup(argv[i++]));
			if (!glb->env)
				panic(glb, CODE_MALLOC, NULL);
		}
	}
}

void	blt_unset(t_glb *glb, char **argv)
{
	size_t	i;

	i = 1;
	g_rval = 0;
	while (argv[i])
	{
		if (f_strchr(argv[i], '='))
			i++;
		else
			env_key_del(glb->env, argv[i++]);
	}
}

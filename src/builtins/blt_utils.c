/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   blt_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbarberi <mbarberi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/23 15:47:56 by mbarberi          #+#    #+#             */
/*   Updated: 2023/06/01 09:31:15 by mbarberi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	blt_compute_argc(char **argv)
{
	int	i;

	i = 0;
	if (!argv)
		return (0);
	while (argv[i])
		i++;
	return (i);
}

bool	env_is_valid_id(char *s)
{
	if (!*s || *s == '=' || *s == '+')
		return (false);
	if (f_isdigit(s[0]))
		return (false);
	while (*s && *s != '=')
	{
		if (!(f_isalnum(*s) || *s == '_'))
		{
			if ((*s == '+') && (*(s + 1) == '='))
				s++;
			else
				return (false);
		}
		s++;
	}
	return (true);
}

static void	blt_export__sort(char **arr)
{
	int		i;
	char	*tmp;

	i = 0;
	while (arr[i] && arr[i + 1])
	{
		if (arr[i + 1] && (env_strcmp(arr[i], arr[i + 1]) > 0))
		{
			tmp = arr[i];
			arr[i] = arr[i + 1];
			arr[i + 1] = tmp;
			i = 0;
		}
		i++;
	}
}

static char	**blt_export__copy_sort(t_glb *glb)
{
	int		i;
	char	**new;

	i = 0;
	new = f_calloc(env_array_get_size(glb->env) + 1, sizeof(char *));
	if (!new)
		panic(glb, CODE_MALLOC, NULL);
	while (glb->env[i])
	{
		new[i] = glb->env[i];
		i++;
	}
	blt_export__sort(new);
	return (new);
}

void	blt_export__print(t_glb *glb)
{
	int		i;
	char	*p;
	char	**new;

	i = 0;
	new = blt_export__copy_sort(glb);
	while (new[i])
	{
		p = f_strchr(new[i], '=');
		if (p)
		{
			*p = 0;
			printf("declare -x %s=\"%s\"\n", new[i], p + 1);
			*p = '=';
		}
		else
			printf("declare -x %s\n", new[i]);
		i++;
	}
	free(new);
}

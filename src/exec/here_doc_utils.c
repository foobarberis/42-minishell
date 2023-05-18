/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbarberi <mbarberi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/18 12:16:05 by mbarberi          #+#    #+#             */
/*   Updated: 2023/05/18 16:21:06 by mbarberi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	here_doc_count_words(char *buf)
{
	int	word;

	word = 1;
	while (*buf)
	{
		if ((!f_isspace(*buf) && *(buf + 1) == '$')
			|| (f_isspace(*buf) && !f_isspace(*(buf + 1)) && *(buf + 1))
			|| (!f_isspace(*buf) && f_isspace(*(buf + 1))))
			word++;
		buf++;
	}
	return (word);
}

static int	here_doc_split(char **arr, char *buf)
{
	int		i;
	char	c;
	char	*p;

	i = 0;
	p = buf;
	while (*p && *buf)
	{
		if (f_isspace(*p))
			while (*p && f_isspace(*p))
				p++;
		else
			while (*p && (!f_isspace(*p)))
				if (*++p == '$')
					break ;
		c = *p;
		*p = 0;
		arr[i] = f_strdup(buf);
		if (!arr[i++])
			return (env_array_destroy(arr, i), 1);
		*p = c;
		buf = p;
	}
	return (0);
}

static int	here_doc_substitute_values(char **env, char **arr)
{
	char	*tmp;
	char	*value;

	while (*arr)
	{
		if (**arr == '$')
		{
			value = env_getenv(env, *arr + 1);
			if (*(*arr + 1) == '?')
				tmp = f_itoa(g_rval);
			else if (value)
				tmp = f_strdup(value);
			else
				tmp = f_strdup("");
			if (!tmp)
				return (env_array_destroy(arr, env_array_get_size(arr)), 1);
			free(*arr);
			*arr = tmp;
		}
		arr++;
	}
	return (0);
}

static char	*here_doc_unsplit(char **arr)
{
	int		i;
	char	*tmp;
	char	*new;

	i = 1;
	new = f_strdup(arr[0]);
	if (!new)
		return (NULL);
	while (arr[i])
	{
		tmp = f_strjoin(new, arr[i++]);
		free(new);
		if (!tmp)
			return (NULL);
		new = tmp;
	}
	return (new);
}

char	*here_doc_expand_variables(char **env, char *buf)
{
	char	*s;
	char	**new;

	new = f_calloc(here_doc_count_words(buf) + 1, sizeof(char *));
	if (!new)
		return (free(buf), NULL);
	if (here_doc_split(new, buf))
		return (free(buf), NULL);
	if (here_doc_substitute_values(env, new))
		return (free(buf), NULL);
	free(buf);
	s = here_doc_unsplit(new);
	env_array_destroy(new, env_array_get_size(env));
	return (s);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utility_function.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vburton <vburton@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/30 14:15:35 by vburton           #+#    #+#             */
/*   Updated: 2023/05/30 14:15:39 by vburton          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t				i;
	const unsigned char	*u1;
	const unsigned char	*u2;

	i = 0;
	u1 = (const unsigned char *)s1;
	u2 = (const unsigned char *)s2;
	while (u1[i] && u1[i] == u2[i] && i < n)
		i++;
	if (i == n)
		return (0);
	return (u1[i] - u2[i]);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*substr;
	char	*new_str;
	size_t	s_len;
	size_t	i;

	s_len = f_strlen(s);
	if (s == NULL || s_len < start)
		return (f_strdup(""));
	if (start + len < s_len)
		substr = (char *)malloc((len + 1) * sizeof(char));
	else
		substr = (char *)malloc((s_len - start + 1) * sizeof(char));
	if (substr == NULL)
		return (NULL);
	i = start;
	new_str = substr;
	while (i < (start + len) && *(s + i))
		*new_str++ = *(s + i++);
	*new_str = '\0';
	return (substr);
}

char	**ft_splitbis(char const *s, char **res, char c)
{
	int	i;
	int	j;
	int	x;

	i = 0;
	x = 0;
	while (s[i])
	{
		while (s[i] == c)
			i++;
		j = 0;
		while (s[i + j] != c && s[i + j])
		{
			if (s[i + j + 1] == '\0' || s[i + j +1] == c)
				res[x++] = ft_substr(s, i, j + 1);
			j++;
		}
		i = i + j;
	}
	res[x] = NULL;
	return (res);
}

char	**ft_split(char const *s, char c)
{
	int		i;
	int		len;
	char	**res;

	if (!s)
		return (NULL);
	i = 0;
	len = 0;
	while (s[i])
	{
		while (s[i] && s[i] == c)
			i++;
		while (s[i] && s[i] != c)
			i++;
		if (s[i] == c || (s[i] == '\0' && s[i - 1] != c))
			len++;
	}
	res = malloc(sizeof(char *) * (len + 1));
	if (!res)
		return (NULL);
	res = ft_splitbis(s, res, c);
	return (res);
}

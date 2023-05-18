#include "../inc/minishell.h"

void	print_double_array(char **array, char *title)
{
	int	i;

	i = 0;
	while (array[i])
	{
		printf("%s : %s \n", title, array[i]);
		i++;
	}
}

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
		return ((char *) s1);
	if (!s1)
		return ((char *) s2);
	size_tot = f_strlen((char *) s1) + f_strlen((char *) s2);
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

#include "../../inc/minishell.h"

char	*ft_strdup(const char *s1)
{
	size_t	i;
	size_t	len_s1;
	char	*dup;

	i = 0;
	len_s1 = ft_strlen((char *)s1);
	dup = malloc(sizeof(char) * len_s1 + 1);
	if (!dup)
		return (NULL);
	if (len_s1 == 0)
	{
		dup[i] = '\0';
		return (dup);
	}
	while (i < len_s1)
	{
		dup[i] = s1[i];
		i++;
	}
	dup[i] = '\0';
	return (dup);
}

/* Voir pour changer definitivement les fonctions f_strlen, f_strdup et f_strjoin*/

void	here_doc(char *limiter, char **string)
{
	char	*line;
	char	*buff;

	*string = readline(">");
	if (f_strcmp(*string, limiter) == 0)
		return (free(*string));
	while (1)
	{
		line = readline(">");
		if (line == NULL)
			return ;
		buff = ft_strdup(*string);
		free(*string);
		*string = ft_strjoin(buff, "\n");
		free(buff);
		if (f_strcmp(line, limiter) == 0)
			break ;
		buff = ft_strdup(*string);
		free(*string);
		*string = ft_strjoin(buff, line);
		free(line);
		free(buff);
	}
	free(line);
}

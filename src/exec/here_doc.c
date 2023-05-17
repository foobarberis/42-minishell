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

int	here_doc(char *limiter, char **string)
{
	char	*line;
	char	*buff;

	*string = readline(">");
	if (f_strcmp(*string, limiter) == 0)
		return (free(*string), SUCCESS);
	while (1)
	{
		line = readline(">");
		if (line == NULL)
			return (SUCCESS);
		buff = ft_strdup(*string);
		if (!buff)
			return (CODE_MALLOC);
		free(*string);
		*string = ft_strjoin(buff, "\n");
		if (!*string)
			return (CODE_MALLOC);
		free(buff);
		if (f_strcmp(line, limiter) == 0)
			break ;
		buff = ft_strdup(*string);
		if (!buff)
			return (CODE_MALLOC);
		free(*string);
		*string = ft_strjoin(buff, line);
		if (!*string)
			return (CODE_MALLOC);
		free(line);
		free(buff);
	}
	free(line);
	return (SUCCESS);
}

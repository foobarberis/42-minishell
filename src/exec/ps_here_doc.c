#include "../../inc/minishell.h"

int	loop(char *limiter, char ***string, char **line, char **buff);

char	*ft_strdup(const char *s1)
{
	size_t	i;
	size_t	len_s1;
	char	*dup;

	i = 0;
	len_s1 = f_strlen(s1);
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

int	here_doc(char *limiter, char **string)
{
	int		exec_loop;
	char	*line;
	char	*buff;

	buff = NULL;
	line = NULL;
	*string = NULL;
	if (f_strcmp(*string, limiter) == 0)
		return (free(*string), *string = NULL, SUCCESS);
	while (1)
	{
		exec_loop = loop(limiter, &string, &line, &buff);
		if (line == NULL || exec_loop == CODE_MALLOC)
			break ;
	}
	free(line);
	if (exec_loop == CODE_MALLOC)
		return (CODE_MALLOC);
	return (SUCCESS);
}

int	loop(char *limiter, char ***string, char **line, char **buff)
{
	*line = readline(">");
	if (*line == NULL)
		return (SUCCESS);
	*buff = ft_strdup(**string);
	if (!*buff)
		return (CODE_MALLOC);
	free(**string);
	**string = ft_strjoin(*buff, "\n");
	if (!**string)
		return (CODE_MALLOC);
	free(*buff);
	if (f_strcmp(*line, limiter) == 0)
		return (*line = NULL, SUCCESS);
	*buff = ft_strdup(**string);
	if (!*buff)
		return (CODE_MALLOC);
	free(**string);
	**string = ft_strjoin(*buff, *line);
	if (!*string)
		return (CODE_MALLOC);
	free(*line);
	free(*buff);
	return (SUCCESS);
}

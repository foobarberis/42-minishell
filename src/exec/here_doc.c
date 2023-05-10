#include "../../inc/minishell.h"
#include <fcntl.h>


char	*here_doc(char *limiter)
{
	char	*string;
	char	*line;
	char	*buff;

	string = readline(">");
	while (1)
	{
		line = readline(">");
		if (line == NULL)
			return (NULL);
		buff = f_strdup(string);
		free(string);
		string = f_strjoin(buff, "\n");
		free(buff);
		if (f_strcmp(line, limiter) == 0)
			break ;
		buff = f_strdup(string);
		free(string);
		string = f_strjoin(buff, line);
		free(line);
		free(buff);
	}
	if (line)
		free(line);
	return (string);
}

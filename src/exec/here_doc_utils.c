#include "minishell.h"

static int here_doc_count_words(char *buf)
{
	int  word;

	word = 1;
	while (*buf)
	{
		if ((f_isspace(*buf) && !f_isspace(*(buf + 1)) && *(buf + 1)) || (!f_isspace(*buf) && f_isspace(*(buf + 1))))
			word++;
		buf++;
	}
	return (word);
}

static char **here_doc_split(char *buf, int words)
{
	int   i;
	char  c;
	char *p;
	char **new;

	i = 0;
	new = f_calloc(words + 1, sizeof(char *));
	if (!new)
		return (NULL);
	p = buf;
	while (*p && *buf)
	{
		if (f_isspace(*p))
			while (*p && f_isspace(*p))
				p++;
		else
			while (*p && !f_isspace(*p))
				p++;
		c = *p;
		*p = 0;
		new[i++] = f_strdup(buf);
		*p = c;
		buf = p;
	}
	return (new);
}

static void here_doc_substitute_values(char **env, char **arr)
{
	char *value;

	while (*arr)
	{
		if (**arr == '$')
		{
			value = env_getenv(env, *arr + 1);
			free(*arr);
			if (value)
				*arr = f_strdup(value);
			else
				*arr = f_strdup("");
		}
		arr++;
	}
}

static char *here_doc_unsplit(char **arr)
{
	int i;
	char *tmp;
	char *new;

	i = 1;
	new = f_strdup(arr[0]);
	if (!new)
		return (NULL);
	while (arr[i])
	{
		tmp = f_strjoin(new, arr[i++]);
		free(new);
		new = tmp;
	}
	return (new);
}

/* FIXME: Handle strings of the form $HOME$USER */
char *here_doc_expand_variables(char **env, char *buf)
{
	char **new;
	new = here_doc_split(buf, here_doc_count_words(buf));
	here_doc_substitute_values(env, new);
	for (int i = 0; new[i]; i++)
		printf("%s\n", new[i]);
	printf("unsplit: %s\n", here_doc_unsplit(new));
}

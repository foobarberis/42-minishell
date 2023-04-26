#include "../inc/execution.h"

int	main(int argc,char **argv, char **envp)
{
	int 	i;
	int 	j;
	t_token tok;
	t_token	tok1;
	t_token tok2;
	t_token	tok3;
	t_token tok4;
	t_token	tok5;
	t_token tok6;
	t_token	tok7;
//	t_token tok8;
	t_token	tok9;
	t_token tok10;
	t_token	tok11;
	t_env	*env;
	t_glb	glob;
	t_cmd	*cmd;

	i = 0;
	glob.multiple_cmd = 1;
	cmd = malloc(sizeof(t_cmd) * glob.multiple_cmd);
	glob.tok = malloc(sizeof(t_token) * 2);
	if (argc == 5 && argv)
	{
		return (0);
	}
	env = malloc(sizeof(t_env) * 1);
	env->envp = envp;
	glob.env = env;
	tok.word = ft_strdup("cat");
	tok.type = BASIC;
	tok.next = &tok1;
	tok1.word = ft_strdup("<");
	tok1.type = S_INPUT_CHEVRON;
	tok1.next = &tok2;
	tok2.word = ft_strdup("input.txt");
	tok2.type = R_INPUT;
	tok2.next = &tok3;
	tok3.word = ft_strdup("-e");
	tok3.type = BASIC;
	tok3.next = &tok4;
	tok4.word = ft_strdup(">");
	tok4.type = S_OUTPUT_CHEVRON;
	tok4.next = &tok5;
	tok5.word = ft_strdup("output.txt");
	tok5.type = R_OUTPUT;
	tok5.next = &tok6;
	tok6.word = ft_strdup("<");
	tok6.type = S_INPUT_CHEVRON;
	tok6.next = &tok7;
	tok7.word = ft_strdup("input2.txt");
	tok7.type = R_INPUT;
	tok7.next = NULL;
//	tok8.word = ft_strdup("|");
//	tok8.type = S_OUTPUT_CHEVRON;
//	tok8.next = &tok9;
	tok9.word = ft_strdup("echo");
	tok9.type = BASIC;
	tok9.next = &tok10;
	tok10.word = ft_strdup(">");
	tok10.type = S_OUTPUT_CHEVRON;
	tok10.next = &tok11;
	tok11.word = ft_strdup("output_cmd_2.txt");
	tok11.type = R_OUTPUT;
	tok11.next = NULL;
	glob.tok[0] = &tok;
	glob.tok[1] = &tok9;
	initialisation_cmds(cmd, glob);
	while (i < glob.multiple_cmd)
	{
		j = 0;
		print_double_array(cmd[i].args, "array of cmd");
		printf("Path cmd = %s\n", cmd[i].path_cmd);
		while (cmd[i].struct_input && j < cmd[i].struct_input->fd_input)
		{
			printf("input file = %s\n", cmd[i].struct_input[j].input);
			j++;
		}
		j = 0;
		while (cmd[i].struct_output && j < cmd[i].struct_output->fd_output)
		{
			printf("output files = %s\n", cmd[i].struct_output[j].output);

			j++;
		}
		printf("\n");
		i++;
	}
	printf("\nfd_input of cmd 0 = %d\n", cmd[0].final_input);
	printf("fd_output of cmd 0 = %d\n", cmd[0].final_output);
	printf("\nfd_input of cmd 1 = %d\n", cmd[1].final_input);
	printf("fd_output of cmd 1 = %d\n", cmd[1].final_output);
	printf("is builtin cmd 0 = %d\n", cmd[0].builtin);
	printf("is builtin cmd 1= %d\n", cmd[1].builtin);
	single_execution(cmd[0]);

	return (0);
}

void print_double_array(char **array, char *title)
{
	int i;

	i = 0;
	while (array[i])
	{
		printf("%s : %s \n",title, array[i]);
		i++;
	}
}


#include <stdlib.h>

char	*ft_strdup(const char *s)
{
	char	*ptr;
	size_t	len;
	int		i;

	i = 0;
	len = ft_strlen(s);
	ptr = (char *)malloc((len + 1) * sizeof(char));
	if (ptr == NULL)
		return (NULL);
	while (s[i])
	{
		ptr[i] = s[i];
		i++;
	}
	ptr[i] = '\0';
	return (ptr);
}

size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

static size_t	ft_count(char const *s, char c);
static size_t	ft_sublen(char const *s, char c);
static char		**ft_free(char **ptr);
char	*ft_strndup(char const *s, size_t n);


//return an array of string, terminated with NULL
char	**ft_split(char const *s, char c)
{
	size_t	sublen;
	char	**ptr;
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	ptr = (char **)malloc(sizeof(char *) * (ft_count(s, c) + 1));
	if (ptr == 0)
		return (ptr);
	while (s[i])
	{
		while (s[i] == c)
			i++;
		if (s[i] == '\0')
			break ;
		sublen = ft_sublen(s + i, c);
		ptr[j] = ft_strndup(s + i, sublen);
		if (ptr[j] == NULL)
			return (ft_free(ptr));
		j++;
		i = i + sublen;
	}
	ptr[j] = 0;
	return (ptr);
}

//free everything and return NULL
static char	**ft_free(char **ptr)
{
	int	i;

	i = 0;
	while (ptr[i])
	{
		free(ptr[i]);
		i++;
	}
	free(ptr);
	return (NULL);
}

char	*ft_strndup(char const *s, size_t n)
{
	char	*ptr;
	size_t	i;

	i = 0;
	ptr = (char *)malloc(sizeof(char) * (n + 1));
	if (ptr == 0)
		return (ptr);
	while (s[i] && i < n)
	{
		ptr[i] = s[i];
		i++;
	}
	ptr[i] = '\0';
	return (ptr);
}

static size_t	ft_sublen(char const *s, char c)
{
	size_t	i;

	i = 0;
	while (s[i] && s[i] != c)
		i++;
	return (i);
}

//count the number of substring
static size_t	ft_count(char const *s, char c)
{
	size_t	count;
	size_t	i;

	count = 0;
	i = 0;
	while (s[i] == c)
		i++;
	if (s[i] == '\0')
		return (0);
	while (s[i])
	{
		if (s[i] != c && (s[i + 1] == c || s[i + 1] == '\0'))
			count++;
		i++;
	}
	return (count);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	len1;
	size_t	len2;
	char	*ptr;
	int		i;

	len1 = ft_strlen(s1);
	len2 = ft_strlen(s2);
	ptr = (char *)malloc((len1 + len2 + 1) * sizeof(char));
	if (ptr == 0)
		return (ptr);
	i = 0;
	while (s1[i])
	{
		ptr[i] = s1[i];
		i++;
	}
	while (s2[i - len1])
	{
		ptr[i] = s2[i - len1];
		i++;
	}
	ptr[i] = '\0';
	return (ptr);
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

void	ft_free_split(char **array)
{
	int	i;

	i = 0;
	if (array)
	{
		while (array[i])
		{
			free(array[i]);
			i++;
		}
		free(array);
	}
}

int	ft_strcmp(const char *s1, const char *s2)
{
	size_t	i;

	i = 0;
	if (!s1 || !s2)
		return (-1);
	while (s1[i] && s2[i] && s1[i] == s2[i])
	{
		i++;
		if (s1[i] != s2[i])
			return ((unsigned char)s1[i] - (unsigned char)s2[i]);
	}
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}

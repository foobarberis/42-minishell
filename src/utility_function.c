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

static size_t	ft_count(char const *s, char c);
static size_t	ft_sublen(char const *s, char c);
static char		**ft_free(char **ptr);
char			*ft_strndup(char const *s, size_t n);

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

void	ft_bzero(void *b, size_t n)
{
	f_memset(b, 0, n);
}

char	*ft_next_keep(char *keep)
{
	size_t	i;
	size_t	j;
	char	*next;

	i = 0;
	j = 0;
	if (!keep || keep[0] == '\0')
		return (free(keep), keep = NULL, NULL);
	while (keep[i] != '\n' && keep[i])
		i++;
	next = f_calloc((f_strlen(keep) - i + 1), 1);
	if (!next)
		return (free(keep), keep = NULL, NULL);
	if (i != f_strlen(keep))
		i++;
	while (keep[i])
		next[j++] = keep[i++];
	return (free(keep), keep = NULL, next);
}

char	*ft_nl(char *keep)
{
	size_t	i;
	char	*res;

	i = 0;
	if (!keep)
		return (NULL);
	while (keep[i] != '\n' && keep[i])
		i++;
	if (keep[i] == '\n')
		i++;
	res = f_calloc(i + 1, 1);
	if (!res)
		return (NULL);
	i = 0;
	while (keep[i])
	{
		res[i] = keep[i];
		if (keep[i] == '\n')
			break ;
		i++;
	}
	return (res);
}

char	*ft_add_str(char *keep, char *buffer, size_t r)
{
	size_t	i;
	char	*tmp;

	i = 0;
	while (i < r)
		i++;
	buffer[i] = '\0';
	tmp = f_strjoin(keep, buffer);
	return (free(keep), keep = NULL, tmp);
}

char	*seek(int fd, char *keep)
{
	size_t	r;
	char	*buffer;

	r = 1;
	buffer = f_calloc(BUFFER_SIZE + 1, 1);
	if (!buffer)
		return (free(keep), keep = NULL, NULL);
	while (r != 0)
	{
		r = read(fd, buffer, BUFFER_SIZE);
		if ((int)r == -1)
			break ;
		keep = ft_add_str(keep, buffer, r);
		if (!keep)
			return (free(buffer), buffer = NULL, NULL);
		if (f_strchr(keep, '\n'))
			break ;
	}
	if (buffer != keep)
		free(buffer);
	if (r == 0 && keep[0] == '\0')
		return (free(keep), keep = NULL, NULL);
	return (keep);
}

char	*get_next_line(int fd)
{
	char		*next_line;
	static char	*keep;

	if ((fd < 0 || read(fd, 0, 0) < 0) != 0)
	{
		if (keep)
			free(keep);
		keep = NULL;
		return (NULL);
	}
	keep = seek(fd, keep);
	if (!keep)
		return (NULL);
	next_line = ft_nl(keep);
	keep = ft_next_keep(keep);
	if (!next_line)
	{
		free(keep);
		keep = NULL;
	}
	return (next_line);
}

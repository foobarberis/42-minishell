#include "../inc/execution.h"

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

void	*ft_memset(void *b, int c, size_t len)
{
	size_t	i;

	i = 0;
	while (i < len)
	{
		((unsigned char *)b)[i] = (unsigned char)c;
		i++;
	}
	return (b);
}

char	*ft_strchr(const char *s, int c)
{
	size_t	i;

	i = 0;
	while (s[i])
	{
		if (s[i] == (char)c)
			return ((char *)&s[i]);
		i++;
	}
	if (c == 0)
		return ((char *)&s[i]);
	return (NULL);
}

void	ft_bzero(void *b, size_t n)
{
	ft_memset(b, 0, n);
}

void	*ft_calloc(size_t count, size_t size)
{
	void	*res;

	if (count > SIZE_MAX / size)
		return (NULL);
	res = malloc(size * count);
	if (!res)
		return (NULL);
	ft_bzero(res, size * count);
	return (res);
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
	next = ft_calloc((ft_strlen(keep) - i + 1), 1);
	if (!next)
		return (free(keep), keep = NULL, NULL);
	if (i != ft_strlen(keep))
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
	res = ft_calloc(i + 1, 1);
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
	tmp = ft_strjoin(keep, buffer);
	return (free(keep), keep = NULL, tmp);
}

char	*seek(int fd, char *keep)
{
	size_t	r;
	char	*buffer;

	r = 1;
	buffer = ft_calloc(BUFFER_SIZE + 1, 1);
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
		if (ft_strchr(keep, '\n'))
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
t_token *ps_extract_words(t_pars *p)
{
	int      i;
	char    *tmp;
	t_token *tok;

	i = 0;
	tok = malloc(sizeof(t_token) * (p->nw + 1));
	if (!tok)
		return (NULL);
	tmp = p->s;
	while (1)
	{
		tok[i++].word = f_strdup(tmp);
		tmp = f_memchr(tmp, 0, p->len - (tmp - p->s));
		if (tmp - p->s >= p->len)
			break;
		tmp++;
	}
	tok[i].word = NULL;
	return (tok);
}

#include "minishell.h"

static size_t ps_rl_count_words(char *s)
{
	size_t c;
	bool   in;

	c = 0;
	in = false;
	while (*s)
	{
		if (f_isspace(*s))
			in = false;
		else if (!in)
		{
			in = true;
			c++;
		}
		s++;
	}
	return (c);
}

static char *ps_rl_rm_dup_space(char *str)
{
	int  i;
	int  j;
	bool in;
	char *new;

	i = 0;
	j = 0;
	in = true;
	if (!str)
		return NULL;
	new = malloc(sizeof(char) * (f_strlen(str) + 1));
	if (!new)
		return NULL;
	while (str[i])
	{
		if (isspace(str[i]))
		{
			if (!in)
			{
				in = true;
				new[j++] = ' ';
			}
		}
		else
		{
			in = false;
			new[j++] = str[i];
		}
		i++;
	}
	if (j > 0 && f_isspace(new[j - 1]))
		j--;
	new[j] = '\0';
	return new;
}

static void ps_rl_add_null(char *s)
{
	while (*s)
	{
		if (f_isspace(*s))
		{
			*s = 0;
			s++;
		}
		s++;
	}
}

void ps_rl_struct_init(t_pars *p, char *buf)
{
	p->nw = ps_rl_count_words(buf);
	p->s = ps_rl_rm_dup_space(buf);
	free(buf);
	buf = NULL;
	p->len = f_strlen(p->s);
	ps_rl_add_null(p->s);
}



static t_token *parsing(char *buf)
{
	t_pars   tmp;
	t_token *tok;

	ps_rl_struct_init(&tmp, buf);
	// printf("%s\n%ld\n%ld\n", tmp.s, tmp.nw, tmp.len);
	if (!tmp.nw)
		return (free(tmp.s), NULL);
	tok = ps_extract_words(&tmp);
	if (!tok)
		return (free(tmp.s), NULL);
	return (free(tmp.s), tok);
}

int main(const int ac, const char *av[], const char *ep[])
{
	t_glb *glb;
	char  *buf;

	glb = malloc(sizeof(t_glb));
	if (!glb)
		return (EXIT_FAILURE);
	while (1)
	{
		buf = readline("MS $ ");
		if (!buf)
			break;
		glb->tok = parsing(buf);
		if (!glb->tok)
			continue;
		for (int i = 0; glb->tok[i].word; i++)
			printf("%s\n", glb->tok[i].word);
		/* 		if (!glb->tok)
		            return (free(glb), EXIT_FAILURE); */
	}
	// FIXME Free everything
	return (EXIT_SUCCESS);
}

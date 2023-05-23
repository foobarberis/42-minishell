#include "minishell.h"

static char	*here_doc_loop(char *here_doc, char *rl, char *tmp, char *lim)
{
	while (1)
	{
		free(rl);
		rl = readline("> ");
		if (!rl)
			f_dprintf(STDERR_FILENO, ERR_HERE_DOC, lim);
		if (!rl || !f_strcmp(rl, lim))
			break ;
		tmp = f_strjoin(here_doc, rl);
		if (!tmp)
			return (free(here_doc), free(rl), NULL);
		free(here_doc);
		here_doc = f_strjoin(tmp, "\n");
		free(tmp);
		if (!here_doc)
			return (free(rl), NULL);
	}
	return (here_doc);
}

// If any part of word is quoted, the delimiter shall be formed by
// performing quote removal on word, and the here-document lines shall not
// be expanded. Otherwise, the delimiter shall be the word itself.
// https://pubs.opengroup.org/onlinepubs/9699919799/utilities/V3_chap02.html#tag_18_03
/* FIXME: If some part of the delimiter was quoted, it is not recognized i.e <<E"OF" cat*/
char	*here_doc(char *lim)
{
	char	*buf[3];

	buf[0] = f_strdup("");
	if (!buf[0])
		return (NULL);
	buf[1] = NULL;
	buf[2] = NULL;
	return (here_doc_loop(buf[0], buf[1], buf[2], lim));
}

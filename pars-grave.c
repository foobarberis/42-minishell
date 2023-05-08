void ps_token_list_update_indices(t_token **tok)
{
	char     c;
	size_t   i;
	t_token *curr;

	if (!tok)
		return;
	i = 0;
	curr = *tok;
	while (curr)
	{
		if (curr->word[0] == '$')
			i++;
		curr->word_index += i;
		if ((curr->word[0] == '>' || curr->word[0] == '<') && curr->next)
		{
			c = curr->next->word[0];
			if (c != '<' && c != '>' && c != '|')
				i++;
		}
		curr = curr->next;
	}
}

/* void ps_token_list_set_index_word(t_token **tok)
{
	size_t   word;
	t_token *curr;
	bool     sep;

	if (!tok)
		return;
	word = 0;
	sep = false;
	curr = *tok;
	while (curr)
	{
		if ((f_isspace(curr->word[0]) || curr->word[0] == '|') && !sep)
		{
			sep = true;
			word++;
		}
		else if (!(f_isspace(curr->word[0]) || curr->word[0] == '|') && sep)
		{
			sep = false;
			word++;
		}
		curr->word_index = word;
		curr = curr->next;
	}
} */

/* int ps_token_list_has_syntax_error(t_token **tok)
{
	t_token *next;
	t_token *curr;

	if (!tok || !*tok)
		return (0);
	curr = *tok;
	if (curr->word[0] == '|')
		return (f_perror(ERR_SYNTAX), 1);
	while (curr)
	{
		next = curr->next;
		if (ismeta(curr->word[0]) && curr->quote == NONE)
		{
			if (next && (curr->word[0] == '>' || curr->word[0] == '<') && (next->word[0] == '>' || next->word[0] == '<'))
				next = next->next;
			if ((next && ismeta(next->word[0])) || !next)
				return (f_perror(ERR_SYNTAX), 1);
		}
		curr = next;
	}
	return (0);
} */

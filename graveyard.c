int	parsing(t_glb *glb)
{
	parsing_set_index_quote(glb->tok);
	parsing_set_index_word(glb->tok);
	parsing_set_index_cmd(glb->tok);
	parsing_delete_space(glb->tok);
	parsing_delete_quote(glb->tok);
	if (parsing_check_syntax(glb->tok))
		return (1);
	parsing_update_index_word(glb->tok);
	parsing_delete_pipe(glb->tok);
	if (parsing_expand_variables(glb->tok, glb->env))
		return (f_dprintf(STDERR_FILENO, ERR_MALLOC), 1);
	if (parsing_recreate_words(glb->tok))
		return (f_dprintf(STDERR_FILENO, ERR_MALLOC), 1);
	parsing_fill_type(glb->tok);
	parsing_delete_bracket(glb->tok);
	if (parsing_group_words(glb->tok))
		return (f_dprintf(STDERR_FILENO, ERR_MALLOC), 1);
	glb->multiple_cmd = (int)(((t_token *)(&glb->tok + 1))[-1].cmd_index + 1);
	token_array_print(glb->tok); /* FIXME: Remove before review */
	return (0);
}

/* Regroup words between quotes in one string */
int	parsing_group_words(t_token **tok)
{
	size_t i;
	char  *tmp;

	i = 0;
	while (tok[i])
	{
		while (tok[i + 1] && tok[i]->quote && (tok[i]->quote == tok[i + 1]->quote))
		{
			printf("got here\n");
			tmp = NULL; // f_strjoin(tok[i]->word, tok[i+1]->word);
			if (!tmp)
				return (1);
			free(tok[i]->word);
			tok[i]->word = tmp;
			token_array_rm(tok, i + 1);
		}
		i++;
	}
	return (0);
}

/* void parsing_set_index_word(t_token **tok)
{
	bool   sep;
	size_t i;
	size_t word;

	i = 0;
	word = 0;
	sep = false;
	while (tok[i])
	{
		if (!tok[i]->quote)
		{
			if (!sep && (ismeta(*tok[i]->word) || f_isspace(*tok[i]->word)))
			{
				sep = true;
				word++;
			}
			else if (sep && !(ismeta(*tok[i]->word) || f_isspace(*tok[i]->word)))
			{
				sep = false;
				word++;
			}
		}
		tok[i]->word_index = word;
		i++;
	}
} */

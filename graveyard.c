void ps_token_list_fill_types_brackets(t_token **tok)
{
	t_token *curr;

	if (!tok)
		return;
	curr = *tok;
	while (curr)
	{
		if (curr->quote == NONE)
		{
			if (!f_strcmp(curr->word, ">"))
				curr->type = S_OUTPUT_CHEVRON;
			else if (!f_strcmp(curr->word, "<"))
				curr->type = S_INPUT_CHEVRON;
			else if (!f_strcmp(curr->word, ">>"))
				curr->type = D_OUTPUT_CHEVRON;
			else if (!f_strcmp(curr->word, "<<"))
				curr->type = D_INPUT_CHEVRON;
		}
		curr = curr->next;
	}
}

void ps_token_list_fill_types_files(t_token **tok)
{
	t_token *curr;

	if (!tok)
		return;
	curr = *tok;
	while (curr)
	{
		if (curr->quote == NONE)
		{
			if (curr->type == S_INPUT_CHEVRON)
			{
				if (curr->next)
					curr->next->type = R_INPUT;
			}
			else if (curr->type == S_OUTPUT_CHEVRON)
			{
				if (curr->next)
					curr->next->type = R_OUTPUT;
			}
		}
		curr = curr->next;
	}
}

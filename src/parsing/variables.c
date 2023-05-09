#include "minishell.h"

void ps_token_list_recreate_variables(t_token **tok)
{
	char    *tmp;
	t_token *curr;
	t_token *next;

	if (!tok || !*tok)
		return;
	curr = *tok;
	while (curr)
	{
		next = curr->next;
		while (next && curr->word && curr->word[0] == '$' && next->word[0] != '$' && islegal(next->word[0]) && (curr->word_index == next->word_index) && (curr->quote == next->quote))
		{
			tmp = f_strjoin(curr->word, next->word);
			free(curr->word);
			curr->word = tmp;
			ps_token_list_node_rm(tok, next);
			next = curr->next;
			if (curr->word[0] == '$' && curr->word[1] == '?')
				break;
		}
		curr = next;
	}
}

void ps_token_list_expand_variables(t_token **tok, t_env **env)
{
	char    *value;
	t_token *curr;

	if (!tok || !env)
		return;
	curr = *tok;
	while (curr)
	{
		if (curr->word && curr->word[0] == '$' && curr->word[1] && curr->quote != SIMPLE)
		{
			if (curr->word && curr->word[0] == '$' && curr->word[1] == '?')
				value = f_itoa(rval);
			else
				value = env_getenv(env, &curr->word[1]);
			free(curr->word);
			if (value)
				curr->word = value;
			else
			{
				curr->word = f_strdup("");
				free(value);
			}
		}
		curr = curr->next;
	}
}

#include "minishell.h"

static int is_legal(int c)
{
	return (f_isalnum(c) || c == '_' || c == '?' || c == 0);
}

static int recreate_variables_cond(t_token *curr, t_token *next)
{
	if (!curr || !next)
		return (0);
	return (curr->word[0] == '$'
			&& is_legal(next->word[0])
			&& (curr->word_index == next->word_index)
			&& (curr->quote == next->quote));
}

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
		while (recreate_variables_cond(curr, next))
		{
			tmp = f_strjoin(curr->word, next->word);
			free(curr->word);
			curr->word = tmp;
			ps_token_list_node_rm(tok, next);
			next = curr->next;
			if ((curr->word[0] == '$' && curr->word[1] == '?') || (curr->word[0] == '$' && curr->word[1] == 0))
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
		if (curr->word[0] == '$' && curr->quote != SIMPLE)
		{
			if (curr->word[0] == '$' && curr->word[1] == '?')
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

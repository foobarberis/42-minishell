#include "minishell.h"

/* TODO: Add support for ~ expansion */
/* TODO: Add support for $?. $? is expanded first */


void ps_token_list_recreate_variables(t_token **tok)
{
	char    *tmp;
	t_token *curr;
	t_token *next;

	if (!tok || !*tok)
		return;
	curr = *tok;
	next = curr->next;
	while (curr)
	{
		next = curr->next;
		while (next && curr->word[0] == '$' && islegal(next->word[0]) && (curr->word_index == next->word_index) && (curr->quote == next->quote))
		{
			tmp = f_strjoin(curr->word, next->word);
			free(curr->word);
			curr->word = tmp;
			ps_token_list_node_rm(tok, next);
			next = curr->next;
		}
		curr = curr->next;
	}
}

/*
 * Unlike Bash, `echo [$HOME]` should not expand since `[` is actually a
 * built-in that we don't have to handle. Therefore `[` and `[[` are
 * treated as litteral characters. This goes for `echo \$HOME` which
 * produces `$HOME` in Bash but produces `\$HOME` here since `\` is not a
 * metacharacter in MSH.
 * https://unix.stackexchange.com/questions/99185/what-do-square-brackets-mean-without-the-if-on-the-left
 *
 * Also, variable names must be of the form [a-zA-Z_]+[a-zA-Z0-9_]*, so
 * `echo $USER- -> matthieu-`. Since we don't treat \ as a metacharacter
 * `echo $USER\ -> matthieu\`.
 * https://stackoverflow.com/questions/2821043/allowed-characters-in-linux-environment-variable-names
 */
void ps_token_list_expand_variables(t_token **tok, t_env **env)
{
	char    *value;
	t_token *curr;

	if (!tok)
		return;
	curr = *tok;
	while (curr)
	{
		/* FIXME: is_legal_var_name -> env_list_is_valid_id might break some stuff */
		if (curr->word[0] == '$' && curr->word[1] && env_list_is_valid_id(&curr->word[1]) && curr->quote != SIMPLE)
		{
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

#include "minishell.h"

/* ENV */
bool env_list_is_valid_id(char *s)
{
	if (!s || !*s)
		return (false);
	if (f_isdigit(s[0]))
		return (false);
	while (*s && *s != '=')
	{
		if (!(f_isalnum(*s) || *s == '_'))
			return (false);
		s++;
	}
	return (true);
}

int env_split_key_value(char **arr, char *s)
{
	char *p;
	char *q;
	char *tmp;

	if (!s)
		return (0);
	tmp = f_strdup(s);
	if (!tmp)
		return (1);
	p = tmp;
	q = f_strchr(tmp, '=');
	if (q)
		*q++ = 0;
	arr[0] = f_strdup(p);
	if (!arr[0])
		return (free(tmp), 1);
	arr[1] = f_strdup(q);
	if (!arr[1])
		return (free(tmp), free(arr[0]), 1);
	free(tmp);
	return (0);
}

/* WARNING: Free the pointer if it is not needed anymore */
char *env_getenv(t_env **env, const char *key)
{
	t_env *curr;

	if (!env || !*env || !key || !*key)
		return (NULL);
	curr = *env;
	while (curr)
	{
		if (curr->key && !f_strcmp(key, curr->key))
			return (f_strdup(curr->value));
		curr = curr->next;
	}
	return (NULL);
}

void env_list_print(t_env **env)
{
	t_env *curr;

	if (!env || !*env)
		return;
	curr = *env;
	while (curr)
	{
		if (curr->value)
			f_printf("%s=%s\n", curr->key, curr->value);
		curr = curr->next;
	}
}

void env_list_from_array(t_env **env, char **ep)
{
	char   *tmp[2];

	if (!env || !ep)
		return;
	while (*ep)
	{
		tmp[0] = NULL;
		tmp[1] = NULL;
		env_split_key_value(tmp, *ep);
		env_list_node_add(env, env_list_node_create(tmp[0], tmp[1]));
		ep++;
	}
}

t_env *env_list_key_search(t_env **env, char *key)
{
	t_env *curr;

	if (!env || !key)
		return (NULL);
	curr = *env;
	while (curr)
	{
		if (curr->key && !f_strcmp(curr->key, key))
			return (curr);
		curr = curr->next;
	}
	return (NULL);
}

void env_list_key_add(t_env **env, char *key)
{
	t_env *curr;
	char  *tmp[2];

	tmp[0] = NULL;
	tmp[1] = NULL;
	if (!env || !key || env_split_key_value(tmp, key))
		return;
	curr = env_list_key_search(env, tmp[0]);
	if (curr)
	{
		if (curr->value)
			free(curr->value);
		curr->value = tmp[1];
		free(tmp[0]);
	}
	else
		env_list_node_add(env, env_list_node_create(tmp[0], tmp[1]));
}

void env_list_key_del(t_env **env, char *key)
{
	t_env *curr;
	char  *tmp[2];

	tmp[0] = NULL;
	tmp[1] = NULL;
	if (!env || !key || env_split_key_value(tmp, key))
		return;
	curr = env_list_key_search(env, tmp[0]);
	if (curr)
		env_list_node_rm(env, curr);
	free(tmp[0]);
	free(tmp[1]);
}

/* int main(int ac, char *av[], char *ep[])
{
	t_env **env;

	env = env_list_from_array(ep);
	if (!env)
		return (1);
	char *s = f_strdup("PAGER=more");
	env_list_key_add(env, s);
	printf("\nADD\n");
	env_list_print(env);
	printf("\nREMOVE\n");
	env_list_key_del(env, s);
	env_list_print(env);
	free(s);
	env_list_free_all(env);
	return (0);
} */


/* t_env **env_list_from_array(char **ep)
{
	char   *tmp[2];
	t_env **env;

	if (!ep)
		return (NULL);
	env = malloc(sizeof(t_env *));
	if (!env)
		return (NULL);
	*env = NULL;
	while (*ep)
	{
		tmp[0] = NULL;
		tmp[1] = NULL;
		if (env_split_key_value(tmp, *ep))
			return (env_list_free_all(env), NULL);
		env_list_node_add(env, env_list_node_create(tmp[0], tmp[1]));
		ep++;
	}
	return (env);
} */

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbarberi <mbarberi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 10:44:30 by mbarberi          #+#    #+#             */
/*   Updated: 2023/05/05 11:21:40 by mbarberi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
#define MINISHELL_H

#include "mlc.h"
#include <readline/history.h>  /* history readline */
#include <readline/readline.h> /* readline */
#include <signal.h>            /* signal, sigaction etc. */
#include <stdbool.h>           /* bool */
#include <stddef.h>            /* size_t, int64_t etc. */
#include <stdio.h>             /* DEBUG */
#include <stdlib.h>            /* malloc, free */
#include <string.h>            /* DEBUG */
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h> /* write, sleep, usleep */

typedef struct s_token t_token;
typedef struct s_env   t_env;
typedef struct s_glb   t_glb;

#define ERR_SYNTAX "minishell: syntax error.\n"
#define ERR_PARSING "minishell: parsing error\n"

enum e_types
{
	BASIC,
	S_INPUT,  /* < */
	D_INPUT,  /* << */
	S_OUTPUT, /* > */
	D_OUTPUT  /* >> */
};

enum e_quote_state
{
	NONE,
	SIMPLE,
	DOUBLE
};

struct s_env
{
	char  *key;
	char  *value;
	t_env *next;
};

struct s_glb
{
	t_env    *env;
	int       multiple_cmd;
	t_token **tok;
};

struct s_token
{
	char    *word;
	int      type;
	int      quote;
	size_t   word_index;
	size_t   cmd_index;
	t_token *next;
};

/* ENV_LIST_UTILS.C */
t_env *env_list_node_create(char *key, char *value);
void   env_list_node_destroy(t_env *node);
void   env_list_node_add(t_env **env, t_env *node);
void   env_list_node_rm(t_env **env, t_env *node);
void   env_list_free_all(t_env **env);
t_env *env_list_goto_last(t_env **env);

/* TOKEN_LIST_UTILS.C */
t_token *ps_token_list_node_create(char *s);
void     ps_token_list_node_destroy(t_token *node);
void     ps_token_list_node_add(t_token **tok, t_token *node);
void     ps_token_list_node_rm(t_token **tok, t_token *node);
void     ps_token_list_free_all(t_token **tok);
t_token *ps_token_list_goto_last(t_token **tok);

/* ENV.C */
bool   env_list_is_valid_id(char *s);
int    env_split_key_value(char **arr, char *s);
char  *env_getenv(t_env **env, const char *key);
void   env_list_print(t_env **env);
void   env_list_from_array(t_env **env, char **ep);
t_env *env_list_key_search(t_env **env, char *key);
void   env_list_key_add(t_env **env, char *key);
void   env_list_key_del(t_env **env, char *key);

/* BUILTINS */
int blt_export(t_glb *glb, char *key);
int blt_unset(t_glb *glb, char *key);
int blt_cd(int argc, char **argv, t_glb *glb);

/* PARSING.C */
bool ismeta(int c);
int  is_legal_var_char(int c);
int  ps_token_list_update_quote_state(char c, int state);
bool ps_line_has_balanced_quotes(char *s);
void ps_token_list_from_array(t_token **tok, char *s);
void ps_token_list_print(t_token **tok);
void ps_token_list_mark_quotes(t_token **tok);
void ps_token_list_set_index_word(t_token **tok);
void ps_token_list_set_index_cmd(t_token **tok);
void ps_token_list_update_indices(t_token **tok);
void ps_token_list_delete_unquoted_spaces(t_token **tok);
void ps_token_list_delete_unquoted_quotes(t_token **tok);
void ps_token_list_delete_unquoted_pipes(t_token **tok);
void ps_token_list_delete_unquoted_dollar(t_token **tok);
void ps_token_list_recreate_words(t_token **tok);
void ps_token_list_recreate_variables(t_token **tok);
void ps_token_list_fill_type(t_token **tok);
void ps_token_list_expand_variables(t_token **tok, t_env **env);
void ps_token_list_group_words(t_token **tok);
int  ps_token_list_has_syntax_error(t_token **tok);
int  parsing(t_glb *glb);

/* SIGNAL.C */
void sigint_handler(int sig);

#endif

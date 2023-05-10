/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbarberi <mbarberi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 10:44:30 by mbarberi          #+#    #+#             */
/*   Updated: 2023/05/10 10:53:19 by mbarberi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
#define MINISHELL_H

#include "mlc.h"
#include <fcntl.h>             /* ?? */
#include <readline/history.h>  /* history readline */
#include <readline/readline.h> /* readline */
#include <signal.h>            /* signal, sigaction etc. */
#include <stdbool.h>           /* bool */
#include <stddef.h>            /* size_t, int64_t etc. */
#include <stdio.h>             /* DEBUG */
#include <stdlib.h>            /* malloc, free */
#include <string.h>            /* DEBUG */
#include <sys/stat.h>          /* ?? */
#include <sys/types.h>         /* ?? */
#include <sys/wait.h>          /* ?? */
#include <unistd.h>            /* write, sleep, usleep */

extern int rval; /* return value of the last command or pipeline */

typedef struct s_token  t_token;
typedef struct s_env    t_env;
typedef struct s_glb    t_glb;
typedef struct s_input  t_input;
typedef struct s_output t_output;
typedef struct s_cmd    t_cmd;

/*
 * DEFINE
 */
#define ERR_SYNTAX "minishell: syntax error.\n"
#define ERR_PARSING "minishell: parsing error.\n"
#define ERR_ID "minishell: export: not a valid identifier.\n"
#define ERR_MALLOC "minishell: malloc() failed.\n"
#define SUCCESS 0
#define ERROR -2
#define ERROR_REDIRECT -3
#define NO_REDIRECTION -4
#define REDIRECTION 0
#ifndef BUFFER_SIZE
#define BUFFER_SIZE 1000
#endif

/*
 * ENUM
 */
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

enum e_builtin
{
	ECHO = 1,
	CD,
	PWD,
	EXPORT,
	UNSET,
	ENV,
	EXIT = -1,
};

enum e_redirect
{
	TRUNC,
	HERE_DOC,
};

/*
 * STRUCT
 */
struct s_env
{
	char  *key;
	char  *value;
	t_env *next;
};

struct s_glb
{
	char    **ep;
	t_env   **env;
	t_token **tok;
	int       multiple_cmd;
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

struct s_input
{
	char *input;
	char *limiter;
	int   type;
	int   fd_input;
};

struct s_output
{
	char *output;
	int   type;
	int   fd_output;
};

struct s_cmd
{
	int       fd[2];
	int       pid;
	int       builtin;
	char    **env;
	char    **args;
	char     *path_cmd;
	int       final_input;
	int       final_output;
	t_input  *struct_input;
	t_output *struct_output;
};

/*
 * PROTOTYPES
 */
/* ENV */
t_env *env_list_node_create(char *key, char *value);
void   env_list_node_destroy(t_env *node);
void   env_list_node_add(t_env **env, t_env *node);
void   env_list_node_rm(t_env **env, t_env *node);
void   env_list_free_all(t_env **env);
t_env *env_list_goto_last(t_env **env);
size_t env_list_get_size(t_env **env);

bool   env_list_is_valid_id(char *s);
int    env_split_key_value(char **arr, char *s);
char  *env_getenv(t_env **env, const char *key);
void   env_list_print(t_env **env);
void   env_list_from_array(t_env **env, char **ep);
t_env *env_list_key_search(t_env **env, char *key);
void   env_list_key_add(t_glb *glb, char *key);
void   env_list_key_del(t_glb *glb, char *key);
char  *env_join_key_value(t_env *node);
void   env_envp_del(char **envp);
int    env_envp_update(t_glb *glb);

/* BUILTINS */
int    blt_export(t_glb *glb, char **argv);
int    blt_unset(t_glb *glb, char **argv);
int    blt_cd(int argc, char **argv, t_glb *glb);
size_t blt_compute_argc(char **argv);

/* PARSING */
t_token *ps_token_list_node_create(char *s);
void     ps_token_list_node_destroy(t_token *node);
void     ps_token_list_node_add(t_token **tok, t_token *node);
void     ps_token_list_node_rm(t_token **tok, t_token *node);
void     ps_token_list_free_all(t_token **tok);
t_token *ps_token_list_goto_last(t_token **tok);

int ps_token_list_check_for_null(t_token **tok);

int   ismeta(int c);
int   islegal(int c);
char *f_itoa(intmax_t n);
bool  ps_line_has_balanced_quotes(char *s);
int   ps_token_list_from_array(t_token **tok, char *s);
void  ps_token_list_print(t_token **tok);
void  ps_token_list_set_index_quote(t_token **tok);
void  ps_token_list_set_index_word(t_token **tok);
void  ps_token_list_update_index_word(t_token **tok);
void  ps_token_list_set_index_cmd(t_token **tok);
void  ps_token_list_delete_space(t_token **tok);
void  ps_token_list_delete_quote(t_token **tok);
void  ps_token_list_delete_pipe(t_token **tok);
void  ps_token_list_delete_bracket(t_token **tok);
void  ps_token_list_recreate_words(t_token **tok);
void  ps_token_list_recreate_variables(t_token **tok);
void  ps_token_list_fill_type(t_token **tok);
void  ps_token_list_expand_variables(t_token **tok, t_env **env);
void  ps_token_list_group_words(t_token **tok);
bool  ps_token_list_has_syntax_error(t_token **tok);
int   parsing(t_glb *glb);

/* MISC */
void sigint_handler(int sig);

/* EXEC */
/*** pe_is_builtin ***/
int ps_is_builtin(char *cmd);

/*** pe_get_cmd_path ***/
int ps_get_path_cmd(char *cmd, char **envp, char **path_cmd);

/*** pe_fill_all_cmd ***/
int ps_initialisation_cmds(t_cmd *cmd, t_glb *glob, t_token **tok);

/*** ex_here_doc ***/
void ps_here_doc(char *limiter);

/*** ps_fill_arrays_struct_cmd ***/
int ps_fill_struct_input(t_token *tok, t_input *input, int nb_input);
int ps_fill_struct_output(t_token *tok, t_output *output, int nb_output);
int ps_fill_args_array(t_token *tok, char **cmd, int nb_args);

/*** ps_fill_cmd_struct ***/
int ps_fill_cmd_struct(t_cmd *cmd, t_token *tok);

/*** pe_redirect ***/
int ps_open_redirect(t_input *in, t_output *out, int *final_out, int *final_in);

/*** ex_builtin ***/
void ex_builtin(int builtin, char **arg);

/*** ex_execution ***/
int ex_execution(t_cmd *cmd, int nb_cmd);

/*** tility_fonctions ***/
char **ft_split(char const *s, char c);
int    ft_strncmp(const char *s1, const char *s2, size_t n);
void   ft_free_split(char **array);
void   print_double_array(char **array, char *title);
char  *get_next_line(int fd);

/*** free ***/
void free_t_cmd(t_cmd *cmd, int nb_cmd);

#endif

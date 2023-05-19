#ifndef MINISHELL_H
#define MINISHELL_H

#include "mlc.h"
#include <dirent.h>            /* opendir */
#include <fcntl.h>             /* ?? */
#include <linux/limits.h>      /* PATH_MAX */
#include <readline/history.h>  /* history readline */
#include <readline/readline.h> /* readline */
#include <signal.h>            /* signal, sigaction etc. */
#include <stdbool.h>           /* bool */
#include <stddef.h>            /* size_t, int64_t etc. */
#include <stdio.h>             /* printf */
#include <stdlib.h>            /* malloc, free */
#include <string.h>            /* DEBUG */
#include <sys/stat.h>          /* ?? */
#include <sys/types.h>         /* ?? */
#include <sys/wait.h>          /* ?? */
#include <unistd.h>            /* write, sleep, usleep */

extern int g_rval; /* return value of the last command or pipeline */

typedef struct s_token  t_token;
typedef struct s_env    t_env;
typedef struct s_glb    t_glb;
typedef struct s_input  t_input;
typedef struct s_output t_output;
typedef struct s_cmd    t_cmd;

/*
 * DEFINE
 */
#define KEY_NOT_FOUND -1
#define ERR_SYNTAX "minishell: syntax error.\n"
#define ERR_PARSING "minishell: parsing error.\n"
#define ERR_ID "minishell: export: not a valid identifier.\n"
#define ERR_MALLOC "minishell: malloc() failed.\n"
#define ERR_HERE_DOC "minishell: warning: here-document delimited by end-of-file (wanted `%s')\n"
#define CODE_MALLOC 2
#define SUCCESS 0
#define ERROR -1
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
struct s_glb
{
	char    **env;
	t_token **tok;
	char     *rl;
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

struct s_cmd
{
	int 	is_valid;
	int       fd[2];
	int       pid;
	int       is_builtin;
	char    **env;
	char    **args;
	char     *path_cmd;
	int       final_input;
	int       final_output;
	char	*input;
	char	*limiter;
	int 	expand_here_doc;
	int		type_in;
	int		is_here_doc;
	char 	*string_here_doc;
	char *output;
	int   type_out;
	t_glb *glb;
};

/*
 * PROTOTYPES
 */
char *here_doc_expand_variables(char **env, char *buf);
void panic(t_glb *glb, int code, t_cmd *cmd);

/* ENV */
int    env_strcmp(const char *s1, const char *s2);
size_t env_array_get_size(char **env);
void   env_array_destroy(char **env, size_t size);
char **env_array_realloc(char **env, size_t size);
int    env_key_get_pos(char **env, char *key);

char  *env_getenv(char **env, char *s);
char **env_key_add(char **env, char *key);
void   env_key_del(char **env, char *key);
char **env_init(char **envp);

/* BUILTINS */
bool env_is_valid_id(char *s);
int  blt_export(t_glb *glb, int argc, char **argv);
void blt_export__print(t_glb *glb);
int  blt_unset(t_glb *glb, int argc, char **argv);
int  blt_env(t_glb *glb);
int  blt_echo(char **argv);
int  blt_pwd(void);
int  blt_exit(t_glb *glb, t_cmd *cmd, int argc, char **argv);
int  blt_cd(t_glb *glb, int argc, char **argv);
int  blt_compute_argc(char **argv);

/* PARSING */
t_token *ps_token_list_node_create(char *s);
void     ps_token_list_node_destroy(t_token *node);
void     ps_token_list_node_add(t_token **tok, t_token *node);
void     ps_token_list_node_rm(t_token **tok, t_token *node);
void     ps_token_list_free(t_token **tok);
t_token *ps_token_list_goto_last(t_token **tok);

int   ismeta(int c);
char *f_itoa(intmax_t n);
bool  ps_line_has_balanced_quotes(t_token **tok);
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
void  ps_token_list_recreate_words(t_glb *glb);
void  ps_token_list_recreate_variables(t_glb *glb);
void  ps_token_list_fill_type(t_token **tok);
void  ps_token_list_expand_variables(t_glb *glb);
void  ps_token_list_group_words(t_glb *glb);
bool  ps_token_list_has_syntax_error(t_token **tok);
int   parsing(t_glb *glb);

/* MISC */
void sigint_handler(int sig);

/* EXEC */
int exec(t_glb *glob);

/*** pe_is_builtin ***/
int ps_is_builtin(char *cmd);

/*** pe_get_cmd_path ***/
char *ps_get_path_cmd(char *cmd, char **envp, char *path_cmd);

/*** pe_fill_all_cmd ***/
int  ps_initialisation_cmds(t_cmd *cmd, t_glb *glob);
void init_to_null_cmd_struct(t_cmd *cmd);

/*** ex_here_doc ***/
char *here_doc(char *lim);

/*** ps_fill_arrays_struct_cmd ***/
int ps_get_args_cmd(t_token *tok, t_cmd *cmd, int nb_args, size_t index);
int ps_get_here_doc(t_token *tok, t_cmd *cm, size_t index);

/*** ps_get_redirect ***/
int ps_get_input(t_token *tok, t_cmd *cmd, size_t index);
int ps_get_output(t_token *tok, t_cmd *cmd, size_t index);

/*** ps_fill_cmd_struct ***/
int count_type(t_token *tok, int type1, int type2, size_t i);

/*** pe_redirect ***/
int open_output(t_cmd *files);
int open_input(t_cmd *files);

/*** ex_builtin ***/
void ex_builtin(t_glb *glb, t_cmd * cmd, int builtin, char **arg);

/*** ex_redirection ***/
void nothing_to_redirect(t_cmd *cmd, size_t i, size_t nb_cmd);
void in_out_redirect(t_cmd *cmd, size_t i);
void in_redirect(t_cmd *cmd, size_t i, size_t nb_cmd);
void out_redirect(t_cmd *cmd, size_t i);

/*** utility_fonctions ***/
char **ft_split(char const *s, char c);
int    ft_strncmp(const char *s1, const char *s2, size_t n);
char  *ft_strjoin(char const *s1, char const *s2);

/*** free ***/
int  free_t_cmd(t_cmd *cmd, int nb_cmd);
void close_fd(t_cmd *cmd, int nb_cmd);
char	**ft_free_double_array(char **ptr);

#endif

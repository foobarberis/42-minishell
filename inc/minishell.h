/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbarberi <mbarberi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/23 16:14:24 by mbarberi          #+#    #+#             */
/*   Updated: 2023/06/13 08:47:03 by mbarberi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../mlc/inc/mlc.h"
# include <dirent.h>            /* opendir */
# include <fcntl.h>             /* ?? */
# include <linux/limits.h>      /* PATH_MAX */
# include <readline/history.h>  /* history readline */
# include <readline/readline.h> /* readline */
# include <signal.h>            /* signal, sigaction etc. */
# include <stdbool.h>           /* bool */
# include <stddef.h>            /* size_t, int64_t etc. */
# include <stdio.h>             /* printf */
# include <stdlib.h>            /* malloc, free */
# include <string.h>            /* DEBUG */
# include <sys/stat.h>          /* ?? */
# include <sys/types.h>         /* ?? */
# include <sys/wait.h>          /* ?? */
# include <unistd.h>            /* write, sleep, usleep */

extern uint8_t			g_rval;

typedef struct s_glb	t_glb;
typedef struct s_cmd	t_cmd;
typedef struct s_token	t_token;

/*
 * DEFINE
 */
# define ERR_MALLOC "minishell: malloc() failed\n"
# define ERR_SYNTAX "minishell: syntax error near unexpected token `%s'\n"

# define KEY_NOT_FOUND -1
# define CODE_MALLOC 512
# define SUCCESS 0
# define ERROR -1
# define ERROR_REDIRECT -3
# define NO_REDIRECTION -4
# define REDIRECTION 0
# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1000
# endif

/*
 * ENUM
 */
enum e_types
{
	BASIC,
	S_INPUT,
	D_INPUT,
	S_OUTPUT,
	D_OUTPUT
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
	EXIT
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
	char		**env;
	t_token		**tok;
	t_token		***split;
	t_cmd		**cmd;
	char		*rl;
	int			multiple_cmd;
	uint8_t		old_rval;
};

struct s_token
{
	char	*word;
	int		type;
	int		quote;
	size_t	word_index;
	size_t	cmd_index;
};

struct s_cmd
{
	int		is_valid;
	int		fd[2];
	int		pid;
	int		is_builtin;
	int		final_input;
	int		final_output;
	int		type_in;
	int		is_here_doc;
	int		type_out;
	char	**env;
	char	**args;
	char	*path_cmd;
	char	*input;
	char	*output;
	char	*string_hc;
	t_glb	*glb;
};

/*
 * PROTOTYPES
 */

void	panic(t_glb *glb, int code, t_cmd *cmd);

/* ENV */
int		env_strcmp(const char *s1, const char *s2);
size_t	env_array_get_size(char **env);
void	env_array_destroy(char **env, size_t size);
char	**env_array_realloc(char **env, size_t size);
int		env_key_get_pos(char **env, char *key);

char	*env_getenv(char **env, char *s);
char	**env_key_add(char **env, char *key);
void	env_key_del(char **env, char *key);
char	**env_init(char **envp);

/* BUILTINS */
bool	env_is_valid_id(char *s);
void	blt_export(t_glb *glb, int argc, char **argv);
void	blt_export__print(t_glb *glb);
void	blt_unset(t_glb *glb, char **argv);
void	blt_env(t_glb *glb);
void	blt_echo(char **argv);
void	blt_pwd(void);
void	blt_exit(t_glb *glb, t_cmd *cmd, int argc, char **argv);
void	blt_cd(t_glb *glb, int argc, char **argv);
int		blt_compute_argc(char **argv);

/* PARSING */
char	*token_array_to_string(t_token **tok);
t_token	*token_struct_create(char *word);
t_token	**token_array_create(char *s);
void	token_struct_destroy(t_token *p);
void	token_array_destroy(t_token **tok);
void	token_array_rm(t_token **tok, size_t pos);
t_token	***token_split_create(t_token **tok);
void	token_split_destroy(t_token ***split);
int		ismeta(int c);
int		is_legal(int c);
char	*f_itoa(intmax_t n);
size_t	get_max_cmd(t_token **tok);
char	*here_doc_expand_variables(char **env, char *buf);
int		parsing_recreate_variables(t_token **tok);
char	*get_value(char **env, char *key, int quote);
void	parsing_set_index_quote(t_token **tok);
void	parsing_set_index_word(t_token **tok);
void	parsing_set_index_cmd(t_token **tok);
void	parsing_update_index_word(t_token **tok);
void	parsing_delete_space(t_token **tok);
void	parsing_delete_quote(t_token **tok);
void	parsing_delete_pipe(t_token **tok);
void	parsing_delete_bracket(t_token **tok);
int		parsing_expand_variables(t_token **tok, char **env);
int		parsing_recreate_words(t_token **tok);
int		parsing_recreate_strings(t_token **tok);
int		parsing_here_doc(t_token **tok, char **env);
void	parsing_fill_type(t_token **tok);
int		parsing_check_syntax(t_token **tok);
t_token	***parsing_split_into_cmd(t_token **tok);
int		parsing(t_glb *glb);

/* MISC */
void	sigint_handler(int sig);
void	sig_child_handler(int status);
void	sigquit_handler(int sig);

/* EXEC */
int		ps_is_builtin(char *cmd);
int		ps_initialisation_cmds(t_cmd *cmd, t_glb *glob);
int		ps_get_redirect(t_token **tok, t_cmd *cmd);
int		ps_get_args_cmd(t_token **tok, t_cmd *cmd);
int		ps_get_redirect(t_token **tok, t_cmd *cmd);
int		count_type(t_token **tok, int type);
int		open_output(t_cmd *files);
int		open_input(t_cmd *files);
char	*ps_get_path_cmd(char *cmd, char **envp, char *path_cmd);
char	*here_doc(char *lim);
void	in_out_redirect(t_cmd *cmd, size_t i);

int		exec(t_glb *glob);
void	ex_builtin(t_glb *glb, t_cmd *cmd, int builtin, char **arg);
void	nothing_to_redirect(t_cmd *cmd, size_t i, size_t nb_cmd);
void	in_redirect(t_cmd *cmd, size_t i, size_t nb_cmd);
void	out_redirect(t_cmd *cmd, size_t i);
void	exec_n_close_unused(t_cmd *cmd);

int		free_t_cmd(t_cmd *cmd, int nb_cmd);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
char	**ft_split(char const *s, char c);
char	**ft_free_double_array(char **ptr);
void	close_fd(t_cmd *cmd, int nb_cmd);

#endif

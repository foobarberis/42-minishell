#ifndef EXECUTION_H
# define EXECUTION_H

# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
# include "minishell.h"
# include "mlc.h"

# define SUCCESS 0
# define ERROR	-2
# define ERROR_REDIRECT -3
# define NO_REDIRECTION -4
# define REDIRECTION 0
# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1000
# endif

/*** Builtin ***/
enum
{
	ECHO = 1,
	CD,
	PWD,
	EXPORT,
	UNSET,
	ENV,
	EXIT = -1,
};

/*** redirection ***/
enum
{
	TRUNC,
	HERE_DOC,
};

typedef struct s_input	t_input;
typedef struct s_output	t_output;
typedef struct s_cmd	t_cmd;

struct	s_input
{
	char	*input;
	char	*limiter;
	int		type;
	int		fd_input;
};

struct	s_output
{
	char	*output;
	int		type;
	int		fd_output;
};

/*Need all this element for the execution of every t_cmd*/

struct	s_cmd
{
	int			fd[2];
	int			pid;
	int			builtin;
	char		**env;
	char		**args;
	char		*path_cmd;
	int			final_input;
	int			final_output;
	t_input		*struct_input;
	t_output	*struct_output;
};

/*** pe_is_builtin ***/
int		ps_is_builtin(char *cmd);

/*** pe_get_cmd_path ***/
int		ps_get_path_cmd(char *cmd, char **envp, char **path_cmd);

/*** pe_fill_all_cmd ***/
int		ps_initialisation_cmds(t_cmd *cmd, t_glb *glob, t_token **tok);

/*** ex_here_doc ***/
void	ps_here_doc(char *limiter);

/*** ps_fill_arrays_struct_cmd ***/
int		ps_fill_struct_input(t_token *tok, t_input *input, int nb_input);
int		ps_fill_struct_output(t_token *tok, t_output *output, int nb_output);
int		ps_fill_args_array(t_token *tok, char **cmd, int nb_args);

/*** ps_fill_cmd_struct ***/
int		ps_fill_cmd_struct(t_cmd *cmd, t_token *tok);

/*** pe_redirect ***/
int		ps_open_redirect(t_input *in, t_output *out, int *final_out, int *final_in);

/*** ex_builtin ***/
void	ex_builtin(int builtin, char **arg);

/*** ex_execution ***/
int		ex_execution(t_cmd *cmd, int nb_cmd);

/*** tility_fonctions ***/
char	*f_strdup(const char *s);
size_t	f_strlen(const char *s);
char	**ft_split(char const *s, char c);
char	*f_strjoin(char const *s1, char const *s2);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
void	ft_free_split(char **array);
void	print_double_array(char **array, char *title);
int		f_strcmp(const char *s1, const char *s2);
char	*get_next_line(int fd);

/*** free ***/
void	free_t_cmd(t_cmd *cmd, int nb_cmd);

#endif

#ifndef EXECUTION_H
# define EXECUTION_H

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include "minishell.h"
#include "mlc.h"

#define SUCCESS 0
#define ERROR	-2
#define ERROR_REDIRECT -3

/*** Type ***/
enum
{
	BASIC,
	R_INPUT,
	R_OUTPUT,
	S_INPUT_CHEVRON,
	D_INPUT_CHEVRON,
	S_OUTPUT_CHEVRON,
	D_OUTPUT_CHEVRON,
}

/*** Builtin ***/
enum
{
	NONE,
	ECHO,
	CD,
	PWD,
	EXPORT,
	UNSET,
	ENV,
	EXIT = -1,
}

/*** redirection ***/
enum
{
	TRUNC,
	HERE_DOC,
}

typedef struct s_input t_input;
typedef struct s_output t_output;
typedef struct s_cmd t_cmd; 		//t_cmd represent everything between two pipe.

struct s_input
{
	char	*input;
	char	*limiter;
	int		type;
	int 	fd_input;
};

struct s_output
{
	char	*output;
	int		type;
	int 	fd_output;
};

/*Need all this element for the execution of every t_cmd*/

struct s_cmd
{
	int			fd[2];
	int			pid;
	int			builtin;
	t_env		*env;
	char		**cmd;
	char		*path_cmd;
	int			*final_input;
	int			*final_output;
	t_input		*struct_input;
	t_output	*struct_output;
};

/*definition of globale struct to contain the infomation given by readline
struct s_glob
{
	int		multiple_cmd;
	char 	**envp,
	t_cmd	*cmd;
}
*/

/*** pe_get_cmd_path ***/
char	*ft_path_cmd(char *cmd, char **envp);

/*** ex_here_doc ***/
void	ft_here_doc(char *limiter);

/*** ps_fill_arrays_struct_cmd ***/
int	fill_input_array(t_token tok, t_input *input);
int	fill_output_array(t_token tok, t_output *output);
int	fill_cmd_array(t_token tok, char ***cmd);

/*** ps_fill_cmd_struct ***/
int	fill_cmd_struct(t_glob	glob);

/*** pe_get_cmd_path ***/
void	get_path_cmd(char *cmd, char **envp, char **path_cmd);

/*** pe_redirect ***/
int	open_all_redirects(t_input *input, t_output *output, char **final_output, char **final_input);

#endif
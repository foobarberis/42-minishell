#ifndef EXECUTION_H
# define EXECECUTION_H

#include "minishell.h"
#include "mlc.h"

#define SUCCESS 0
#define ERROR_REDIRECT -2

enum	builtin 
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

enum	redirect
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
};

struct s_output
{
	char	*output;
	int		type;
};

/*Need all this element for the execution of every t_cmd*/

struct s_cmd
{
	int			fd[2];
	int			pid;
	char		*path_cmd;
	char		**cmd;
	char		**env;
	t_input		*input;
	t_output	*output;
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

#endif
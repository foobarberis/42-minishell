#ifndef EXECUTION_H
# define EXECECUTION_H

#include "minishell.h"
#include "mlc.h"

enum	builtin 
{
	NONE,
	ECHO,
	CD,
	PWD,
	EXPORT,
	UNSET,
	ENV,
	EXIT,
}

enum	redirect
{
	TRUNC,
	APPEND,
}

typedef struct s_redirect t_redirect;

struct s_redirects
{
	char	*file;
	int		type;
};


/*** pe_get_cmd_path ***/
char	*ft_path_cmd(char *cmd, char **envp);

/*** ex_here_doc ***/
void	ft_here_doc(char *limiter);

#endif
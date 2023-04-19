#include "minishell.h"
#include "execution.h"

void	open_all_redirects(t_redirect *file)
{
	int	i;

	i = 0;
	while (files[i]->file)
	{
		if (files[i]->type == TRUNC)
			open(files[i]->file, O_WRONLY | O_TRUNC | O_CREAT, 0644);
		else
			open(files[i]->file, O_WRONLY | O_APPEND | O_CREAT, 0644);
	}
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbarberi <mbarberi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/23 15:53:01 by mbarberi          #+#    #+#             */
/*   Updated: 2023/05/30 12:27:29 by mbarberi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <linux/limits.h>

void	blt_pwd(void)
{
	char	buf[PATH_MAX];

	g_rval = 0;
	if (!getcwd(buf, PATH_MAX))
	{
		g_rval = 1;
		perror("minishell: pwd");
	}
	else
		printf("%s\n", buf);
}

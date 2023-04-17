/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbarberi <mbarberi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 10:44:30 by mbarberi          #+#    #+#             */
/*   Updated: 2023/04/17 11:42:41 by mbarberi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
#define MINISHELL_H

#include "mlc.h"
#include <readline/readline.h> /* readline */
#include <signal.h>            /* signal, sigaction etc. */
#include <stddef.h>            /* size_t, int64_t etc. */
#include <stdlib.h>            /* malloc, free */
#include <unistd.h>            /* write, sleep, usleep */
#include <stdbool.h>

typedef struct s_token t_token;
typedef struct s_glb   t_glb;

struct s_glb
{
	t_token *tok;
};

struct s_token
{
	char    *word;
	int      type;
	char   **arg;
	int      size;
	bool     builtin;
	t_token *next;
	t_token *prev;
};

/* PARSING */
t_token *parsing(char *buf);

#endif

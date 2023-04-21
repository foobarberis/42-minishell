/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vburton <vburton@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 10:44:30 by mbarberi          #+#    #+#             */
/*   Updated: 2023/04/21 11:26:07 by vburton          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
#define MINISHELL_H

#include "mlc.h"
#include <readline/readline.h> /* readline */
#include <signal.h>            /* signal, sigaction etc. */
#include <stdbool.h>
#include <stddef.h> /* size_t, int64_t etc. */
#include <stdio.h>  /* DEBUG */
#include <stdlib.h> /* malloc, free */
#include <unistd.h> /* write, sleep, usleep */

typedef struct s_token t_token;
typedef struct s_env   t_env;
typedef struct s_glb   t_glb;

enum
{
	BLTIN,
	PROG,
	ARG,
	SP
};

struct s_env
{
	char **envp;
	size_t size;
};

struct s_glb
{
	t_env   *env;
	t_token *tok;
};

// see man execve
struct s_token
{
	char *word;
	int   type;

};

/* PARSING */
t_token *parsing(char *buf);

/* PS_ENV */
int    env_export(t_env *env, char *key);
int    env_unset(t_env *env, char *key);
void   env_array_free(char **envp, size_t size);
void   env_array_print(t_env *env);
char **env_array_dup(char **envp, size_t size);

/* PS_ENV_UTILS */
int    env_key_search(t_env *env, char *key);
int    env_key_add(t_env *env, char *key);
int    env_key_del(t_env *env, int pos);
size_t env_key_get_len(char *key);
t_env *env_init(char **envp);

/* BLT_1 */
int blt_export(t_glb *glb, char *key);
int blt_unset(t_glb *glb, char *key);

#endif

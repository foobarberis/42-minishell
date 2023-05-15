/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbarberi <mbarberi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/11 10:32:38 by mbarberi          #+#    #+#             */
/*   Updated: 2023/05/15 12:30:20 by mbarberi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static size_t	f_ndigit(intmax_t n, int baselen)
{
	size_t	l;

	l = 0;
	if (n <= 0)
		l += 1;
	while (n)
	{
		l++;
		n /= baselen;
	}
	return (l);
}

char	*f_itoa(intmax_t n)
{
	char		*s;
	size_t		l;
	uintmax_t	nb;

	l = f_ndigit(n, 10);
	s = malloc(l + 1);
	if (!s)
		return (NULL);
	s[l] = '\0';
	if (n < 0)
		s[0] = '-';
	else if (!n)
		s[0] = '0';
	nb = f_abs(n);
	while (nb)
	{
		s[--l] = (char)(nb % 10 + '0');
		nb /= 10;
	}
	return (s);
}

int	ismeta(int c)
{
	return (c == '<' || c == '>' || c == '|');
}

int	ps_token_list_from_array(t_token **tok, char *s)
{
	char	buf[2];
	t_token	*tmp;

	buf[1] = '\0';
	tmp = NULL;
	while (*s)
	{
		buf[0] = *s++;
		tmp = ps_token_list_node_create(buf);
		if (!tmp)
			return (f_dprintf(STDERR_FILENO, ERR_MALLOC), 1);
		ps_token_list_node_add(tok, tmp);
	}
	return (0);
}

/* FIXME: Remove */
void	ps_token_list_print(t_token **tok)
{
	t_token	*curr;

	curr = *tok;
	printf("%-15s | %-15s | %-15s | %-15s | %-15s\n",
		"type", "quote", "char *", "word", "cmd");
	printf("-------------------------------------------------------------------"
		"--------\n");
	while (curr)
	{
		if (curr->word)
		{
			if (curr->word[0])
				printf("%-15d | %-15d | %-15s | %-15ld | %-15ld\n", curr->type,
					curr->quote, curr->word, curr->word_index, curr->cmd_index);
			else
				printf("%-15d | %-15d | %-15s | %-15ld | %-15ld\n", curr->type,
					curr->quote, "(empty)", curr->word_index, curr->cmd_index);
		}
		curr = curr->next;
	}
	f_printf("\n");
}

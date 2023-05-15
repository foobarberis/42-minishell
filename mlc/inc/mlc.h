/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlc.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbarberi <mbarberi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/03 16:59:04 by mbarberi          #+#    #+#             */
/*   Updated: 2023/05/13 16:57:04 by mbarberi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MLC_H
# define MLC_H

# include <stdlib.h>
# include <unistd.h>
# include <stdint.h>
# include <stdarg.h>

/* STRING */
/* standard */
void		*f_memchr(const void *s, int c, size_t n);
int			f_memcmp(const void *s1, const void *s2, size_t n);
void		*f_memcpy(void *d, const void *s, size_t n);
void		*f_memmem(const void *h0, size_t hlen, const void *n0, size_t nlen);
void		*f_memmove(void *d, const void *s, size_t n);
void		*f_memset(void *s, int c, size_t n);

char		*f_strchr(const char *s, int c);
int			f_strcmp(const char *s1, const char *s2);
char		*f_strdup(const char *str);
char		*f_strjoin(char const *s1, char const *s2);
size_t		f_strlcat(char *d, const char *s, size_t n);
size_t		f_strlcpy(char *d, const char *s, size_t n);
size_t		f_strlen(const char *s);
size_t		f_strnlen(const char *s, size_t n);
char		*f_strnstr(const char *h, const char *n, size_t m);
/* non-standard */
void		*f_memrchr(const void *s, int c, size_t n);

/* STDLIB */
/* standard */
int			f_atoi(const char *s);
void		*f_calloc(size_t n, size_t m);
/* non-standard */
double		f_atof(const char *s);

/* STDIO */
/* standard */
int			f_printf(const char *s, ...);
int			f_dprintf(int fd, const char *s, ...);
/* non-standard */
ssize_t		f_uputnbr(int fd, unsigned int n, char *base);
ssize_t		f_sputnbr(int fd, int n, char *base);
ssize_t		printf__putchar(int fd, char c);
ssize_t		printf__putstr(int fd, char *s);
ssize_t		printf__arg(int fd, char c, va_list *ap);

/* CTYPE */
/* standard */
int			f_isalpha(int c);
int			f_isalnum(int c);
int			f_isascii(int c);
int			f_isdigit(int c);
int			f_islower(int c);
int			f_isspace(int c);
int			f_isupper(int c);

/* MISC */
uintmax_t	f_abs(intmax_t n);
char		*f_file_to_array(char *file);
#endif

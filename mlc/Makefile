# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mbarberi <mbarberi@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/11/16 17:06:24 by mbarberi          #+#    #+#              #
#    Updated: 2023/05/13 16:57:51 by mbarberi         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Edit the $(NAME) and $(SRCS) variables as necessary.
NAME		:=	libft.a

SRCS		:=	ctype/f_isalnum.c \
				ctype/f_isalpha.c \
				ctype/f_isascii.c \
				ctype/f_isdigit.c \
				ctype/f_islower.c \
				ctype/f_isspace.c \
				ctype/f_isupper.c \
				misc/f_abs.c \
				misc/f_file_to_array.c \
				stdio/f_dprintf.c \
				stdio/f_printf.c \
				stdio/printf_utils.c \
				stdio/f_putnbr.c \
				stdlib/f_atof.c \
				stdlib/f_atoi.c \
				stdlib/f_calloc.c \
				string/f_memchr.c \
				string/f_memcmp.c \
				string/f_memcpy.c \
				string/f_memmem.c \
				string/f_memmove.c \
				string/f_memrchr.c \
				string/f_memset.c \
				string/f_strdup.c \
				string/f_strjoin.c \
				string/f_strlcat.c \
				string/f_strlcpy.c \
				string/f_strlen.c \
				string/f_strnlen.c \
				string/f_strnstr.c \
				string/f_strchr.c \
				string/f_strcmp.c

CC			:=	cc
RM			:=	rm

CFLAGS		:=	-Wall -Wextra -Werror -O3
LDFLAGS		:=	$(CFLAGS)
RMFLAGS		:=	-f

SRCDIR		:=	src
OBJDIR		:=	obj
INCDIR		:=	inc

# Edit the $(HEADERS) variable as necessary.
HEADERS		:=	$(INCDIR)/mlc.h

LINK.o		:=	$(CC) $(LDFLAGS)
COMPILE.c	:=	$(CC) -I$(INCDIR) $(CFLAGS) -c
REMOVE		:=	$(RM) $(RMFLAGS)

SOURCES		:=	$(addprefix $(SRCDIR)/, $(SRCS))
OBJECTS		:=	$(patsubst $(SRCDIR)/%.c, $(OBJDIR)/%.o, $(SOURCES))

$(OBJDIR)/%.o: $(SRCDIR)/%.c
	@mkdir -p $(@D)
	$(COMPILE.c) $< -o $@

all: $(NAME)

$(OBJECTS): $(HEADERS) Makefile

$(NAME): $(OBJECTS)
	ar -rcs $(NAME) $^

clean:
	$(REMOVE) $(OBJECTS)

fclean: clean
	$(REMOVE) $(NAME)

re: fclean all

.PHONY:	all clean fclean re

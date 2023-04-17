# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mbarberi <mbarberi@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/01/23 21:40:52 by mbarberi          #+#    #+#              #
#    Updated: 2023/04/17 10:48:58 by mbarberi         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# If necessary we can use $(info VARIABLE:$(VARIABLE)) to debug.
# We can also use make -d.

# Edit the $(NAME) and $(SRCS) variables as necessary.
NAME		:=	minishell
SRCS		:=	main.c parsing.c

CC			:=	cc
RM			:=	rm

CFLAGS		:=	-Wall -Wextra -lreadline -g3 -fsanitize=address # -Werror
LDFLAGS		:=	$(CFLAGS)
RMFLAGS		:=	-f

SRCDIR		:=	src
OBJDIR		:=	obj
INCDIR		:=	inc
LFTDIR		:=	mlc

# Edit the $(HEADERS) variable as necessary.
HEADERS		:=	$(INCDIR)/minishell.h

INCFLAGS	:= -I$(INCDIR) -I$(LFTDIR)/inc

LINK.o		:=	$(CC) $(LDFLAGS)
COMPILE.c	:=	$(CC) $(INCFLAGS) $(CFLAGS) -c
REMOVE		:=	$(RM) $(RMFLAGS)

SOURCES		:=	$(addprefix $(SRCDIR)/, $(SRCS))
OBJECTS		:=	$(patsubst $(SRCDIR)/%.c, $(OBJDIR)/%.o, $(SOURCES))

$(OBJDIR)/%.o: $(SRCDIR)/%.c
	@mkdir -p $(@D)
	$(COMPILE.c) $< -o $@

all: libft $(NAME)

$(OBJECTS): $(HEADERS) Makefile

$(NAME): $(OBJECTS)
	$(LINK.o) -o $(NAME) $^

libft:
	make -C $(LFTDIR)

clean:
	$(REMOVE) $(OBJECTS)

fclean: clean
	$(REMOVE) $(NAME)

re: fclean all

.PHONY:	all libft clean fclean re

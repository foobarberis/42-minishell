# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mbarberi <mbarberi@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/01/23 21:40:52 by mbarberi          #+#    #+#              #
#    Updated: 2023/05/06 10:12:51 by mbarberi         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# If necessary we can use $(info VARIABLE:$(VARIABLE)) to debug.
# We can also use make -d.

# Edit the $(NAME) and $(SRCS) variables as necessary.
NAME		:=	minishell
SRCS		:=	env.c \
				env_list_utils.c \
				ex_execution.c \
				free.c \
				main.c \
				parsing.c \
				ps_fill_all_cmd.c \
				ps_fill_arrays_cmd_struct.c \
				ps_fill_cmd_struct.c \
				ps_get_cmd_path.c \
				ps_here_doc.c \
				ps_is_builtin.c \
				ps_redirects.c \
				signal.c \
				token_list_utils.c \
				utility_function.c

CC			:=	cc
RM			:=	rm

SRCDIR		:=	src
OBJDIR		:=	obj
INCDIR		:=	inc
SYSINC		:=	/usr/include
SYSLIB		:=	/usr/lib
MLCDIR		:=	mlc

INCFLAGS	:= -I$(INCDIR) -I$(SYSINC) -I$(MLCDIR)/inc
LIBFLAGS	:= -L$(MLCDIR) -lreadline -lft
# CFLAGS	:=	-Wall -Wextra -Werror
CFLAGS		:= -g3 -Wall -Wextra -Wconversion -Wdouble-promotion -Wno-unused-parameter -Wno-unused-function -Wno-sign-conversion -fsanitize=undefined,address
LDFLAGS		:=	$(CFLAGS)
RMFLAGS		:=	-f

# Edit the $(HEADERS) variable as necessary.
HEADERS		:=	$(INCDIR)/minishell.h $(INCDIR)/execution.h

REMOVE		:=	$(RM) $(RMFLAGS)

SOURCES		:=	$(addprefix $(SRCDIR)/, $(SRCS))
OBJECTS		:=	$(patsubst $(SRCDIR)/%.c, $(OBJDIR)/%.o, $(SOURCES))

$(OBJDIR)/%.o: $(SRCDIR)/%.c
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) $(INCFLAGS) -c $< $(LIBFLAGS) -o $@

all: libft $(NAME)

$(OBJECTS): $(HEADERS) Makefile

$(NAME): $(OBJECTS)
	$(CC) $(OBJECTS) $(CFLAGS) $(INCFLAGS) $(LIBFLAGS) -o $(NAME)

libft:
	make -C $(MLCDIR)

clean:
	$(REMOVE) $(OBJECTS)
	make -C $(MLCDIR) clean

fclean: clean
	$(REMOVE) $(NAME)
	make -C $(MLCDIR) fclean

re: fclean all

.PHONY:	all libft clean fclean re

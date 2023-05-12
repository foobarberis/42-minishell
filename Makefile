# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mbarberi <mbarberi@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/01/23 21:40:52 by mbarberi          #+#    #+#              #
#    Updated: 2023/05/12 11:15:01 by mbarberi         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# If necessary we can use $(info VARIABLE:$(VARIABLE)) to debug.
# We can also use make -d.

# Edit the $(NAME) and $(SRCS) variables as necessary.
NAME		:=	minishell
SRCS		:=	builtins/blt_utils.c \
				builtins/cd.c \
				builtins/echo.c \
				builtins/env.c \
				builtins/exit.c \
				builtins/export_unset.c \
				builtins/pwd.c \
				env/environ.c \
				env/env_list_utils.c \
				env/env_utils.c \
				env/key.c \
				exec/ex_builtin.c \
				exec/exec.c \
				exec/ex_execution.c \
				exec/free.c \
				exec/ps_fill_all_cmd.c \
				exec/ps_fill_arrays_cmd_struct.c \
				exec/ps_fill_cmd_struct.c \
				exec/ps_get_cmd_path.c \
				exec/ps_here_doc.c \
				exec/ps_is_builtin.c \
				exec/ps_redirects.c \
				exec/utility_function.c \
				misc/free.c \
				misc/signal.c \
				parsing/delete.c \
				parsing/index.c \
				parsing/parsing.c \
				parsing/parsing_utils.c \
				parsing/syntax.c \
				parsing/token_list_utils.c \
				parsing/type.c \
				parsing/variables.c \
				parsing/word.c \
				main.c

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
HEADERS		:=	$(INCDIR)/minishell.h

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

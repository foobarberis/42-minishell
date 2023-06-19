# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: vburton <vburton@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/01/23 21:40:52 by mbarberi          #+#    #+#              #
#    Updated: 2023/06/19 15:05:48 by vburton          ###   ########.fr        #
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
				env/environ_add.c \
				env/environ_utils.c \
				exec/ex_builtin.c \
				exec/ex_close.c \
				exec/ex_execution.c \
				exec/ex_free.c \
				exec/ex_redirects.c \
				exec/ps_fill_all_cmd.c \
				exec/ps_get_args.c \
				exec/ps_get_path_cmd.c \
				exec/ps_get_redirect.c \
				exec/ps_is_builtin.c \
				exec/ps_redirects.c \
				exec/utility_function.c \
				misc/signal.c \
				parsing/delete.c \
				parsing/here_doc.c \
				parsing/here_doc_expand.c \
				parsing/index.c \
				parsing/parsing.c \
				parsing/parsing_utils.c \
				parsing/split.c \
				parsing/syntax.c \
				parsing/token_arr_utils.c \
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
# CFLAGS		:=	-O3 -Wall -Wextra -Werror
CFLAGS		:= -g3 -fPIE -Wall -Wextra -Wconversion -Wdouble-promotion -Wno-unused-parameter -Wno-unused-function -Wno-sign-conversion #-fsanitize=undefined,address
RMFLAGS		:=	-f

# Edit the $(HEADERS) variable as necessary.
HEADERS		:=	$(INCDIR)/minishell.h

REMOVE		:=	$(RM) $(RMFLAGS)

SOURCES		:=	$(addprefix $(SRCDIR)/, $(SRCS))
OBJECTS		:=	$(patsubst $(SRCDIR)/%.c, $(OBJDIR)/%.o, $(SOURCES))

$(OBJDIR)/%.o: $(SRCDIR)/%.c
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) $(INCFLAGS) -c $< -o $@

all: libft $(NAME)

$(OBJECTS): $(HEADERS) Makefile

$(NAME): $(OBJECTS) $(MLCDIR)/libft.a
	$(CC) $(OBJECTS) $(LIBFLAGS) -o $(NAME)

libft:
	make -C $(MLCDIR)

clean:
	$(REMOVE) $(OBJECTS)
	make -C $(MLCDIR) clean

fclean: clean
	$(REMOVE) $(NAME)
	make -C $(MLCDIR) fclean

re: fclean
	$(MAKE) all

leaks:    all
			echo "{" > valgrind_ignore_leaks.txt
			echo "leak readline" >> valgrind_ignore_leaks.txt
			echo "    Memcheck:Leak" >> valgrind_ignore_leaks.txt
			echo "    ..." >> valgrind_ignore_leaks.txt
			echo "    fun:readline" >> valgrind_ignore_leaks.txt
			echo "}" >> valgrind_ignore_leaks.txt
			echo "{" >> valgrind_ignore_leaks.txt
			echo "    leak add_history" >> valgrind_ignore_leaks.txt
			echo "    Memcheck:Leak" >> valgrind_ignore_leaks.txt
			echo "    ..." >> valgrind_ignore_leaks.txt
			echo "    fun:add_history" >> valgrind_ignore_leaks.txt
			echo "}" >> valgrind_ignore_leaks.txt
			valgrind --suppressions=valgrind_ignore_leaks.txt --leak-check=full \
    				--show-leak-kinds=all --track-fds=yes \
    				--show-mismatched-frees=yes --read-var-info=yes \
    				--log-file=valgrind.txt ./${NAME}

.PHONY:	all libft clean fclean re

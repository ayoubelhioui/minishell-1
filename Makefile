# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ijmari <ijmari@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/04/21 14:09:12 by marvin            #+#    #+#              #
#    Updated: 2022/05/14 19:21:58 by ijmari           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRC = minishell.c library/ft_split.c library/ft_strtrim.c library/ft_strdup.c library/ft_strlcpy.c \
library/ft_strlen.c library/ft_strstr.c signals.c builtin_cmds/cd.c \
builtin_cmds/pwd.c builtin_cmds/exit.c builtin_cmds/echo.c utils.c builtin_cmds/env.c

CC = cc

#CFLAGS = -Wextra -Werror -Wall
NAME = minishell
READLINE = -lreadline -L ~/goinfre/.brew/opt/readline/lib -I ~/goinfre/.brew/opt/readline/include
SRC_O = $(SRC:.c=.o)

all :$(NAME)
$(NAME) : $(SRC)
	@$(CC) $(READLINE) $(CFLAGS) $(SRC) -o $(NAME)
clean:
	@rm -f $(SRC_O)
fclean:clean
	@rm -f $(NAME)
re: fclean all

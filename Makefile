# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ijmari <ijmari@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/04/21 14:09:12 by marvin            #+#    #+#              #
#    Updated: 2022/05/12 17:49:20 by ijmari           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRC = minishell.c library/ft_split.c library/ft_strtrim.c library/ft_strdup.c library/ft_strlcpy.c library/ft_strlen.c
CC = cc
#CFLAGS = -Wextra -Werror -Wall
NAME = minishell
READLINE = -lreadline -I ~/goinfre/.brew/opt/readline/include
SRC_O = $(SRC:.c=.o)

all :$(NAME)
$(NAME) : $(SRC_O)
	@$(CC) $(READLINE) $(CFLAGS) $(SRC) -o $(NAME)
clean:
	@rm -f $(SRC_O)
fclean:clean
	@rm -f $(NAME)
re: fclean all

SRC = minishell.c library/ft_split.c library/ft_strtrim.c library/ft_strdup.c library/ft_strlcpy.c \
library/ft_strlen.c library/ft_strstr.c library/ft_lstadd_back_bonus.c library/ft_strjoin.c \
library/ft_lstadd_front_bonus.c library/ft_lstlast_bonus.c library/ft_lstnew_bonus.c \
builtin_cmds/cd.c builtin_cmds/pwd.c builtin_cmds/exit.c builtin_cmds/echo.c utils.c builtin_cmds/env.c \
library/ft_lstsize_bonus.c builtin_cmds/built_check.c builtin_cmds/export.c builtin_cmds/unset.c library/ft_isalnum.c  \
quotes_handling.c library/ft_substr.c library/ft_strncmp.c Library/ft_strcmp.c library/join_pl.c library/ft_split_plus.c \
library/ft_export_utils.c library/ft_split_equ.c library/things_done.c signals.c line.c
CC = cc
# CFLAGS = -Wextra -Werror -Wall
NAME = minishell
READLINE = -fsanitize=address -lreadline -L ~/goinfre/.brew/opt/readline/lib -I ~/goinfre/.brew/opt/readline/include
#   
SRC_O = $(SRC:.c=.o)

all :$(NAME)
$(NAME) : $(SRC)
	@stty -echoctl
	@$(CC) $(READLINE) $(CFLAGS) $(SRC) -o $(NAME)
clean:
	@rm -f $(SRC_O)
fclean:clean
	@rm -f $(NAME)
re: fclean all
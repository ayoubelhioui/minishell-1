SRC = minishell_utils.c parsing/initializing_data/initializing_data.c parsing/string_manipulation/string_manipulation.c parsing/string_manipulation/string_manipulation_utils.c parsing/command_argument/command_argument.c parsing/command_argument/command_argument_utils.c parsing/input_output_fd/input_output.c parsing/input_output_fd/pipe_handling.c parsing/errors_handling/errors_handling.c parsing/expanding/expanding.c parsing/expanding/expanding_utils.c parsing/here_doc/here_doc.c minishell.c library/ft_split.c library/ft_strtrim.c library/ft_strdup.c library/ft_strlcpy.c \
library/ft_strlen.c library/ft_strstr.c library/ft_lstadd_back_bonus.c library/errors_printing.c library/ft_strjoin.c \
library/ft_lstadd_front_bonus.c library/ft_lstlast_bonus.c library/ft_lstnew_bonus.c  signals.c list_utils.c \
builtin_cmds/cd.c builtin_cmds/pwd.c builtin_cmds/exit.c builtin_cmds/echo.c utils.c builtin_cmds/env.c \
library/ft_lstsize_bonus.c builtin_cmds/built_check.c builtin_cmds/export.c builtin_cmds/unset.c library/ft_isalnum.c  \
library/ft_substr.c library/ft_strncmp.c Library/ft_strcmp.c library/join_pl.c library/ft_split_plus.c \
library/export_utils2.c  library/things_done.c library/ft_export_utils.c library/ft_split_equ.c line.c library/exec_utils.c library/ft_atoi.c
CC = cc
NAME = minishell
READLINE = -fsanitize=address -lreadline -L /Users/ael-hiou/goinfre/.brew/opt/readline/lib -I /Users/ael-hiou/goinfre/.brew/opt/readline/include
# 
SRC_O = $(SRC:.c=.o)

all :$(NAME)
$(NAME) : $(SRC)
	@$(CC) -g $(READLINE) $(CFLAGS) $(SRC) -o $(NAME)
clean:
	@rm -f $(SRC_O)
fclean:clean
	@rm -f $(NAME)
re: fclean all
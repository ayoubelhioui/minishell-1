#ifndef MINISHELL_H
#define MINISHELL_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "library/library.h"
#include <fcntl.h>
#include <signal.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <sys/types.h>
#include <unistd.h>
#include <dirent.h>
#include "includes/get_next_line.h"

# define SINGLE_QUOTE '\''
# define UNDER_SCORE '_'
# define DOUBLE_QUOTE '\"'
# define EQUAL '='
# define SPACE ' '
# define DOLLAR_SIGN '$'
# define TRUE 1
# define FALSE 0
# define RED_INPUT '<'
# define RED_OUTPUT '>'
# define STD_INPUT 0

typedef struct returned_data
{
    char    *cmd_path;
    char    **args;
    int     input_fd;
    int     output_fd;
    // struct returned_data    *next;
}               t_returned_data;

typedef struct data
{
    char    *context;
    char    **command_and_args;
    int     index;   
}               t_data;

void    ft_free(char **s);
void    replace_with_real_value(t_data *data, char *real_value, char *saver ,int dollar_sign_position);
void    remove_the_word(t_data *data, char *saver, int position);
int     check_unclosed_quotes(char *context);
void    ft_strcpy(char *s, char *str,int start_position, int length);
void    double_quotes(t_data *data, char **env, int is_double_quotes);
void    dollar_sign(t_data *data, char **env);
// void    ft_strcpy(char *s, char *str,int start_position, int length);
char    *search_in_env(char *data, char **env);
void    replacing_space(t_data *data, char quotes);
void	sig_handler(int sig);
void	cd(char **paths, t_list **env);
int		ft_strstr(const char *s1, const char *s2);
void	pwd(void);
void	ft_exit(void);
int		is_int(char *str);
void	ft_echo(const char **s);
void	ft_env(t_list **env);
void	built_check(char	*context, t_list **env);
void	ft_export(t_list **env,char **args);
void	delete_node(t_list **env, int pos);
void	ft_unset(t_list **env, char	**args);
int		ft_equal(char *arg);
#endif

# ifndef MINISHELL_H
# define MINISHELL_H
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include "library/library.h"
# include <fcntl.h>
# include <signal.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <sys/types.h>
# include <unistd.h>
# include <dirent.h>
# include <errno.h>
# include <termios.h>

# define PIPE '|'
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
# define STD_OUTPUT 1
# define ZERO '0'

typedef struct dollar_sign_vars
{
    int index_saver;
    char *env_value;
    char *s1;
    char *s2;
    char *temp;
    char *temp1;
}           t_dollar_sign_vars;

typedef struct returned_data
{
	char					*cmd_path;
    char                    *cmd_dup;
	char					**args;
	int						input_fd;
	int						output_fd;
	int						str_idx;
	int						is_executable;
	char					**new_env;
	int						exit_stat;
	struct returned_data	*next;
}	                        t_returned_data;

typedef struct here_doc_vars
{
    int     p[2];
	char	*s;
    char    *entered_data;
}               t_here_doc_vars;

typedef struct add_space_vars
{
    int     i;
    int     j;
    int     new_string_length;
    char    *new_string;
    int     in_quote;
}           t_add_space_vars;

typedef struct data
{
    char    *context;
    int     value;
    int     index;
}
               t_data;
typedef struct expanding_vars
{
    t_data  data;
    int     in_quote;
    int     is_limiter;
    char    *saver;
    char    *temp;
    int     x;
    int     j;
}           t_expanding;
typedef struct remove_quotes_vars
{
    char    *new_string;
    int      i;
    int      j;
    int     new_string_length;
}               t_remove_quotes_vars;

typedef struct error_handling_vars
{
    int i;
    int in_quote;
}                   t_error_handling_vars;
// typedef struct expanding
// {
//     char *str;
//     char *new_str;
//     int dollar_index;
// }                   t_expanding;
typedef struct g_str
{
	int		exit_stat;
	int		flag_for_here;
	int		saver;
	int		flag;
	int		after_exit;
}	        t_str;
t_str	g_key;
char	*get_next_line(int fd);
void	ft_free(char **s);
char	*expanding(char *str, char **env);
void	returned_data_addback(t_returned_data **returned_data, \
	t_returned_data *new);
void	replace_with_real_value(t_returned_data *returned_data, \
char *real_value, char *saver, int dollar_position);
void	remove_the_word(t_returned_data *data, char *saver, int position);
int		check_unclosed_quotes(char *context);
void	ft_strcpy(char *s, char *str, int start_position, int length);
void	double_quotes(t_data *data, char **env, int is_double_quotes);
void	dollar_sign(t_returned_data *data, char **env, int dollar_position);
char	*search_in_env(char *data, char **env);
void	replacing_space(t_data *data, char quotes);
void	sig_handler(int sig);
void	cd(char **paths, t_list **env);
int		ft_strstr(const char *s1, const char *s2);
void	pwd(void);
void	ft_exit(char *ex);
int		is_int(char *str);
void	ft_echo(char **s);
void	ft_env(t_list **env);
int		built_check(t_returned_data *ret, t_list **env);
void	ft_export(t_list **env, char **args);
void	delete_node(t_list **env, int pos);
void	ft_unset(t_list **env, char	**args);
int		ft_equal(char *arg);
void	searching_for_dollar_sign(t_returned_data **data, char **env);
void	fill_list(t_returned_data *data, char **env, t_list **env_l);
char	*get_command_path(char **env_variables, char *command);
int		built_exist(char *cmd_path);
void	dup_and_close(t_returned_data *data, int c);
void	close_and_wait(t_returned_data *data, int counter);
int		lst_count(t_returned_data *data);
void	close_all_pipes(t_returned_data *head);
void	sig_quit(int sig);
void	ft_free_list(t_returned_data *head);
#endif

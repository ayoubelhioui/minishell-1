/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ijmari <ijmari@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/21 14:03:51 by marvin            #+#    #+#             */
/*   Updated: 2022/05/17 20:19:44 by ijmari           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
#define MINISHELL_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>
#include <unistd.h>
#include <readline/readline.h>
#include <readline/history.h>
#include "library/library.h"
#include <readline/readline.h>
#include <readline/history.h>
#include <termios.h>
#include <sys/types.h>
#include <dirent.h>

#define SINGLE_QUOTES '\''
#define DOUBLE_QUOTES '\"'
void	sig_handler(int sig);
void	cd(char **paths);
int		ft_strstr(const char *s1, const char *s2);
void	pwd(void);
void	ft_exit(void);
int		is_int(char *str);
void	ft_echo(const char **s);
void	ft_env(t_list **env);
void	built_check(char	*context, t_list **env);
void	ft_export(t_list **env,char **args);
void	delete_node(t_list **env, t_list *node, int pos);
void	ft_unset(t_list **env, char	**args);
typedef struct pipe_commands
{
    char *command;
    char *arguments;
}               t_pipe_commands;

typedef struct data
{
    char *command;
    char **arguments;
    char *input_file;
    char *output_file;
}               t_data;

typedef struct pipe_handling
{
	int	(*pipes)[2];
	int	commands;
	int	*ids;
	int	input_fd;
	int	output_fd;
}	t_pipe_handling;

#endif

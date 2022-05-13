/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ijmari <ijmari@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/21 14:03:51 by marvin            #+#    #+#             */
/*   Updated: 2022/05/13 18:18:07 by ijmari           ###   ########.fr       */
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
int		cd_dir(const char *path);
int		ft_strstr(const char *s1, const char *s2);
void	pwd(void);
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

#endif

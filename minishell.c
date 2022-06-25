/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ijmari <ijmari@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/24 10:21:42 by ael-hiou          #+#    #+#             */
/*   Updated: 2022/06/25 14:48:02 by ijmari           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing/expanding/expanding.h"
#include "parsing/errors_handling/errors_handling.h"
#include "parsing/here_doc/here_doc.h"
#include "parsing/input_output_fd/input_output.h"
#include "parsing/command_argument/command_argument.h"
#include "parsing/string_manipulation/string_manipulation.h"
#include "parsing/initializing_data/initializing_data.h"

int	prompt_helper(char *str)
{
	int	len;

	len = 0;
	while (str && str[len])
	{
		if (str[len] != ' ')
			return (1);
		else if (str[len] == ' ' && !str[len + 1])
			return (0);
		len++;
	}
	if (str == NULL)
	{
		printf("exit\n");
		exit(g_key.exit_stat);
	}
	if (ft_strlen(str) == 0)
		return (FALSE);
	printf("PLLL\n");
	if (g_key.after_exit == 1 && str)
		g_key.after_exit = 0;
	return (TRUE);
}

void	prompt(char **env, t_list *new_env)
{
	t_data			entered_data;
	t_returned_data	*returned_data;
	int				ret;

	ret = 0;
	returned_data = NULL;
	entered_data.context = readline("minishell : ");
	if (!prompt_helper(entered_data.context))
		return ;
	add_history(entered_data.context);
	if (error_handling(entered_data.context))
	{
		free(entered_data.context);
		printf("error occured\n");
		return ;
	}
	ret = preparing(&entered_data, new_env, &returned_data);
	if (g_key.flag == 6 && ret == -4)
	{
		ft_free_list(returned_data);
		return ;
	}
	exec(returned_data, env, &new_env);
	ft_free_list(returned_data);
}

int	main(int ac, char **av, char **env)
{
	t_list			*new_env;
	struct termios	termios_new;

	(void)av;
	if (ac != 1)
	{
		printf("Too many arguments\n");
		exit(0);
	}
	create_list(env, &new_env);
	g_key.flag_for_here = 0;
	g_key.after_exit = 0;
	while (TRUE)
	{
		g_key.flag = 0;
		dup2(g_key.saver, 0);
		tcgetattr(0, &termios_new);
		termios_new.c_lflag &= ~(ECHOCTL);
		tcsetattr(0, 0, &termios_new);
		signal(SIGINT, &sig_handler);
		signal(SIGQUIT, SIG_IGN);
		prompt(env, new_env);
	}
}

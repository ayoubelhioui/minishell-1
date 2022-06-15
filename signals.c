/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ijmari <ijmari@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/14 18:55:21 by ijmari            #+#    #+#             */
/*   Updated: 2022/06/15 20:55:21 by ijmari           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	sig_quit(int sig)
{
	if (g_key.flag_for_here == 2)
	{
		printf("Quit: 3\n");
		return ;
	}
	else
		SIG_IGN;
}
void	sig_handler(int sig)
{
	int	saver;

	if (g_key.flag_for_here == 0)
	{
		g_key.exit_stat = 1;
		if (g_key.after_exit == 0)
			write(1, "\n", 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
	else if (g_key.flag_for_here == 1)
	{
		g_key.flag = 6;
		g_key.exit_stat = 1;
		g_key.saver = dup(0);
		close(0);
	}
}

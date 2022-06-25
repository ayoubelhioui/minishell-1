/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-hiou <ael-hiou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/14 18:55:21 by ijmari            #+#    #+#             */
/*   Updated: 2022/06/25 18:40:58 by ael-hiou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	sig_quit(int l)
{
	(void) l;
	g_key.exit_stat = 131;
	exit(131);
}

void	sig_handler(int sig)
{
	(void) sig;
	if (g_key.flag_for_here == 0)
	{
		g_key.exit_stat = 1;
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

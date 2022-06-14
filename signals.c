/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ijmari <ijmari@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/14 18:55:21 by ijmari            #+#    #+#             */
/*   Updated: 2022/06/14 18:57:10 by ijmari           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	sig_handler(int sig)
{
	int	saver;

	if (key.flag_for_here == 0)
	{
		key.exit_stat = 1;
		if (key.after_exit == 0)
			write(1, "\n", 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
	else if (key.flag_for_here == 1)
	{
		key.flag = 6;
		key.saver = dup(0);
		close(0);
	}
}

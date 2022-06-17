/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ijmari <ijmari@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/14 12:49:37 by ijmari            #+#    #+#             */
/*   Updated: 2022/06/17 15:46:23 by ijmari           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_exit(unsigned long long c, char **args)
{
	if (args)
	{
		if (args[2])
		{
		printf("minishell: exit: too many arguments\n");
		g_key.exit_stat = 1;
		exit(g_key.exit_stat);
		}
	}
	exit(g_key.exit_stat);
}

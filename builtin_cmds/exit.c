/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ijmari <ijmari@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/14 12:49:37 by ijmari            #+#    #+#             */
/*   Updated: 2022/06/18 20:41:09 by ijmari           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	exit_atoi(char *str)
{
	int	i;
	unsigned long long temp;
	int	negative;

	i = 0;
	while (str[i] == 32 || str[i] == '\r'
		|| str[i] == '\t' || str[i] == '\n'
		|| str[i] == '\v' || str[i] == '\f')
			i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			negative++;
		i++;
	}
	while ((str[i] >= '0' && str[i] <= '9'))
	{
		if (temp > 9223372036854775807 && !negative)
		{
			printf("HERE 1\n");
			return (-1);
		}
		else if (temp < -9223372036854775807 && negative)
		{
			printf("HERE 2\n");
			return (0);
		}
		temp = (str[i] - 48) + (temp * 10);
		i++;
	}
	if (i <= ft_strlen(str))
	{
		printf("HERE 3\n");
		return (-1);
	}
	if (negative == 1)
		temp *= -1;
	return (temp);
}
void	ft_exit(char *ex)
{
	// if (exit_atoi(ex) == -1 || exit_atoi(ex) == 0)
	// {
	// 	printf("minishell: exit: jne: numeric argument required\n");
	// 	g_key.exit_stat = 255;
	// 	exit(255);
	// }
	exit(g_key.exit_stat);
}

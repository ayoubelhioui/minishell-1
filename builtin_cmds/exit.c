/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ijmari <ijmari@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/14 12:49:37 by ijmari            #+#    #+#             */
/*   Updated: 2022/06/21 14:45:13 by ijmari           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

unsigned long long	exit_atoi(char *str, int *negative)
{
	int	i;
	unsigned long long temp;
	int	flag;

	i = 0;
	while (str[i] == 32 || str[i] == '\r'
		|| str[i] == '\t' || str[i] == '\n'
		|| str[i] == '\v' || str[i] == '\f')
			i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			(*negative)++;
		i++;
	}
	if (!ft_strcmp(str, "-9223372036854775808") && *negative == 1)
		return (9223372036854775808ULL);
	temp = 0;
	while (str[i])
	{
		temp = (str[i] - 48) + (temp * 10);
		if ((temp > 9223372036854775808ULL && *negative == 1) || !ft_isdigit(str[i]))
			return (-1);
		if (temp > 9223372036854775807ULL || !ft_isdigit(str[i]))
			return (-1);
		i++;
	}
	return (temp);
}

void	ft_exit(char **ex)
{
	long long g;
	int	negative = 0;
	long long last;
	g = (long long) exit_atoi(*ex, &negative);
	if (negative == 1 && g != -1)
		g *= -1;
	if (g != -1 && get_length(ex) != 1)
	{
		printf("minishell: exit: too many arguments\n");
		g_key.exit_stat = 1;
		exit(1);
	}
	else if (g == -1)
	{
		printf("minishell: exit: jne: numeric argument required\n");
		g_key.exit_stat = 255;
		exit(255);
	}
	g_key.exit_stat = g;
	exit(g_key.exit_stat);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ijmari <ijmari@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/14 12:48:09 by ijmari            #+#    #+#             */
/*   Updated: 2022/06/28 14:43:41 by ijmari           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	some_ns(char *s)
{
	int	i;

	if (!s)
		return (0);
	if (s[0] != '-')
		return (0);
	i = 1;
	while (s[i])
	{
		if (s[i] != 'n')
			return (0);
		i++;
	}
	return (1);
}

void	ft_echo(char **s)
{
	int		i;
	int		flag;

	flag = 0;
	i = -1;
	if (*s == NULL)
	{
		printf("\n");
		return ;
	}
	while (some_ns(s[++i]))
		flag = 1;
	while (s[i] && s[i + 1])
		printf("%s ", s[i++]);
	if (s[i])
		printf("%s", s[i]);
	if (!flag)
		printf("\n");
	g_key.exit_stat = 0;
}

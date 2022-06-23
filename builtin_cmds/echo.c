/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-hiou <ael-hiou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/14 12:48:09 by ijmari            #+#    #+#             */
/*   Updated: 2022/06/23 19:24:21 by ael-hiou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	print_string(char *s, char c, int flag)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (s[i] == '$' && s[i + 1] == '?')
		{
			if (flag != 1 && !s[i + 2])
				printf("%lld ", g_key.exit_stat);
			else if (flag == 1 && !s[i + 2] && c == 'a')
				printf("%lld\n", g_key.exit_stat);
			else if (flag == 1 && !s[i + 2] && c == 'n')
				printf("%lld", g_key.exit_stat);
			else
				printf("%lld", g_key.exit_stat);
			i++;
		}
		else if (c == 'n' && flag && !s[i + 1])
			printf("%c", s[i]);
		else if (c != 'n' && flag && !s[i + 1])
			printf("%c\n", s[i]);
		else if (!flag && !s[i + 1])
			printf("%c ", s[i]);
		else
			printf("%c", s[i]);
		i++;
	}
}

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
	char	c;

	c = 'a';
	i = -1;
	if (*s == NULL)
		printf("\n");
	while (some_ns(s[++i]))
		c = 'n';
	while (s && s[i])
	{
		print_string(s[i], c, !s[i + 1]);
		i++;
	}
	g_key.exit_stat = 0;
}

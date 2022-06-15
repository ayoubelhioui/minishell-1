/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ijmari <ijmari@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/14 12:48:09 by ijmari            #+#    #+#             */
/*   Updated: 2022/06/14 19:18:58 by ijmari           ###   ########.fr       */
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
			if (flag == 1 && !s[i + 2] && c == 'a')
				printf("%d\n", g_key.exit_stat);
			else if (flag == 1 && !s[i + 2] && c == 'n')
				printf("%d", g_key.exit_stat);
			else
				printf("%d", g_key.exit_stat);
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

void	ft_echo(char **s)
{
	int		i;
	char	c;

	c = 'a';
	i = 0;
	if (*s == NULL)
		printf("\n");
	if (!ft_strcmp(s[0], "-n"))
	{
		c = 'n';
		i = 1;
	}
	else
		i = 0;
	while (s[i])
	{
		print_string(s[i], c, !s[i + 1]);
		i++;
	}
	g_key.exit_stat = 0;
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   global_issues.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ijmari <ijmari@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/24 16:10:35 by ijmari            #+#    #+#             */
/*   Updated: 2022/06/25 13:21:47 by ijmari           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include "../parsing/expanding/expanding.h"

void	export_error(char **split_arg, char **arg, int *i)
{
	printf("export: \'%s\': not a valid identifier\n", arg[(*i)++]);
	if (split_arg)
		ft_free(split_arg);
	g_key.exit_stat = 1;
}

char	*chrdup(char c)
{
	char	*t;

	t = malloc(2);
	t[0] = c;
	t[1] = '\0';
	return (t);
	
}


char	*join_exit_stat(char *str)
{
	char	*temp;
	char	*saver;
	char	*value;
	int		start;
	int		pos;
	char	*it;
	char	*tmp;

	start = 0;
	pos = 0;
	temp = NULL;
	saver = NULL;
	while (str[pos])
	{
		if (str[pos] == '$' && str[pos + 1] == '?')
		{
			value = ft_itoa((int) g_key.exit_stat);
			tmp = saver;
			saver = expanding_join(saver, value);
			free(tmp);
			free(value);
			pos++;
		}
		else
		{
			// it = chrdup(str[pos]);
			tmp = saver;
			it = chrdup(str[pos]);
			saver = expanding_join(saver, it);
			free(tmp);
			free(it);
		}
		pos++;
	}
	return (saver);
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   global_issues.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-hiou <ael-hiou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/24 16:10:35 by ijmari            #+#    #+#             */
/*   Updated: 2022/06/28 21:04:39 by ael-hiou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include "../parsing/expanding/expanding.h"

void	execve_err(t_returned_data *data)
{
	write(2, "minishell: ", 11);
	write(2, data->cmd_dup, ft_strlen(data->cmd_dup));
	write(2, ": ", 2);
	write(2, "command not found\n", 18);
	g_key.exit_stat = 127;
	exit(127);
}

void	export_error(char **split_arg, char **arg, int *i)
{
	printf("export: \'%s\': not a valid identifier\n", arg[(*i)++]);
	if (split_arg)
		ft_free(split_arg);
	g_key.exit_stat = 1;
	if (arg[*i] == NULL)
		g_key.cd_flag = 0;
}

char	*chrdup(char c)
{
	char	*t;

	t = malloc(2);
	t[0] = c;
	t[1] = '\0';
	return (t);
}

char	*expand_exit_stat(char *str, int *pos, char *saver)
{
	char	*value;
	char	*it;
	char	*tmp;

	if (str[*pos] == '$' && str[*pos + 1] == '?')
	{
		value = ft_itoa((int) g_key.exit_stat);
		tmp = saver;
		saver = expanding_join(saver, value);
		free(tmp);
		free(value);
		(*pos)++;
	}
	else
	{
		tmp = saver;
		it = chrdup(str[*pos]);
		saver = expanding_join(saver, it);
		free(tmp);
		free(it);
	}
	return (saver);
}

char	*join_exit_stat(char *str)
{
	char	*saver;
	int		pos;

	pos = 0;
	saver = NULL;
	while (str[pos])
	{
		saver = expand_exit_stat(str, &pos, saver);
		pos++;
	}
	return (saver);
}

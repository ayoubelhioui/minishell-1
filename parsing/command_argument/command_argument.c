/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_argument.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-hiou <ael-hiou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/24 11:31:55 by ael-hiou          #+#    #+#             */
/*   Updated: 2022/06/28 19:44:36 by ael-hiou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "command_argument.h"

int	get_args_length(char **data)
{
	int	i;
	int	counter;

	i = 0;
	counter = 0;
	while (data[i])
	{
		if (!ft_strcmp(data[i], "<") || !ft_strcmp(data[i], ">"))
		{
			i++;
			counter += 2;
			if (!ft_strcmp(data[i], "<") || !ft_strcmp(data[i], ">"))
			{
				i++;
				counter++;
			}
		}
		i++;
	}
	return (counter);
}

void	args_final_touch(t_returned_data *returned_data)
{
	int	i;

	while (returned_data)
	{
		i = 0;
		while (returned_data->args[i])
			back_space(returned_data->args[i++]);
		returned_data = returned_data->next;
	}
}

void	get_cmd_args_helper1(char **data, int *i, \
		int *j, t_returned_data *returned_data)
{
	char	*temp;
	char	*fr;

	if (!ft_strcmp(data[*i], "<") || !ft_strcmp(data[*i], ">"))
	{
		*i += 1;
		if (!ft_strcmp(data[*i], "<") || !ft_strcmp(data[*i], ">"))
			*i += 1;
	}
	else
	{
		temp = data[*i];
		returned_data->args[*j] = remove_quotes(data[*i]);
		if (ft_strstr(returned_data->args[*j], "$?"))
		{
			fr = returned_data->args[*j];
			returned_data->args[*j] = join_exit_stat(returned_data->args[*j]);
			free(fr);
		}
		*j += 1;
		data[*i] = returned_data->args[*j - 1];
		free (temp);
	}
}

void	get_cmd_args_helper(char **data, \
		t_returned_data *returned_data, char **env)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (data[i])
	{
		get_cmd_args_helper1(data, &i, &j, returned_data);
		i++;
	}
	returned_data->cmd_dup = returned_data->args[0];
	returned_data->cmd_path = get_command_path(env, returned_data->args[0]);
	returned_data->args[j] = NULL;
}

int	get_cmd_args(char **data, t_returned_data *returned_data, char **env)
{
	char	**s;
	int		k;
	int		whole_length;

	whole_length = 0;
	k = 0;
	while (returned_data)
	{
		s = ft_split(data[k++], SPACE);
		whole_length = get_length(s) - get_args_length(s);
		if (whole_length == 0)
		{
			ft_free(s);
			returned_data->flag = 1;
			returned_data = returned_data->next;
			continue ;
		}
		if (returned_data->args[0] == NULL)
			free(returned_data->args);
		returned_data->args = malloc(sizeof(char *) * (whole_length + 1));
		get_cmd_args_helper(s, returned_data, env);
		freeing(s);
		returned_data = returned_data->next;
	}
	return (TRUE);
}

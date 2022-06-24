/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_output.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-hiou <ael-hiou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/24 11:19:46 by ael-hiou          #+#    #+#             */
/*   Updated: 2022/06/24 17:57:36 by ael-hiou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "input_output.h"

void	getting_output_fd_helper(char **s, int i, \
t_returned_data *returned_data)
{
	char	*temp;

	if (!ft_strcmp(s[i], ">"))
	{
		temp = remove_quotes(s[i + 1]);
		returned_data->output_fd = \
		open(temp, O_WRONLY | O_CREAT | O_APPEND, 00400 | 00200);
		free (temp);
	}
	else
	{
		temp = remove_quotes(s[i]);
		returned_data->output_fd = open(temp, O_WRONLY \
		| O_CREAT | O_TRUNC, 00400 | 00200);
		free (temp);
	}
}

void	getting_output_fd(char *str, t_returned_data \
*returned_data, int unexisting_file_idx)
{
	char	**s;
	char	*temp;
	int		i;

	s = ft_split(str, SPACE);
	i = 0;
	while (s[i] && i < unexisting_file_idx)
	{
		if (!ft_strcmp(s[i], ">"))
		{
			i++;
			if (returned_data->output_fd != 1)
				close (returned_data->output_fd);
			getting_output_fd_helper(s, i, returned_data);
			if (returned_data->output_fd == -1)
			{
				returned_data->is_executable = FALSE;
				printf("%s\n", strerror(errno));
				break ;
			}
		}
		i++;
	}
	ft_free(s);
}

int	getting_input_fd(char *str, t_returned_data *returned_data, char **s)
{
	int	temp_input;
	int	i;

	i = -1;
	temp_input = returned_data->input_fd;
	while (s[++i])
	{
		if (!ft_strcmp(s[i], "<") && !ft_strcmp(s[i + 1], "<"))
			i += 2;
		else if (!ft_strcmp(s[i], "<"))
		{
			i++;
			returned_data->input_fd = open(s[i], O_RDONLY);
			if (returned_data->input_fd == -1)
			{
				printf("%s:%s\n", s[i], strerror(errno));
				returned_data->is_executable = FALSE;
				return (i);
			}
		}
	}
	return (i);
}

void	getting_input_output_fd(char *str, t_returned_data *temp)
{
	int		unexisting_file_idx;
	char	**s;

	s = ft_split(str, SPACE);
	unexisting_file_idx = getting_input_fd(str, temp, s);
	ft_free (s);
	getting_output_fd(str, temp, unexisting_file_idx);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ijmari <ijmari@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/14 16:01:46 by ijmari            #+#    #+#             */
/*   Updated: 2022/06/14 16:01:53 by ijmari           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	dup_and_close(t_returned_data *data, int c)
{
	if (c == 'i')
	{
		dup2(data->input_fd, STD_INPUT);
		close (data->input_fd);
	}
	else
	{
		dup2(data->output_fd, STD_OUTPUT);
		close (data->output_fd);
	}
}

void	close_and_wait(t_returned_data *data, int counter)
{
	int	i;
	int	status;

	close_all_pipes(data);
	i = 0;
	while (i < counter)
	{
		wait(&status);
		if (WIFEXITED(status))
			key.exit_stat = WEXITSTATUS(status);
		i++;
	}
	key.flag_for_here = 0;
}

int	lst_count(t_returned_data *data)
{
	int	len;

	len = 0;
	while (data)
	{
		len++;
		data = data->next;
	}
	return (len);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-hiou <ael-hiou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/14 16:01:46 by ijmari            #+#    #+#             */
/*   Updated: 2022/06/20 14:07:35 by ael-hiou         ###   ########.fr       */
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

void	close_and_wait(t_returned_data *data, int counter, int *id)
{
	int	i;
	int	status;

	close_all_pipes(data);
	i = 0;
	while (i < counter)
	{
		waitpid(id[i], &status, 0);
		if (WIFEXITED(status))
			g_key.exit_stat = WEXITSTATUS(status);
		if (status == 2)
			g_key.exit_stat= 130;
		if (status == 3)
			g_key.exit_stat = 131;
		i++;
	}
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

void	ft_free(char **ptr)
{
	int	i;

	i = 0;
	while (ptr[i])
		free(ptr[i++]);
	free(ptr);
}

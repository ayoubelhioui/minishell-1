/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ijmari <ijmari@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/22 21:15:45 by ijmari            #+#    #+#             */
/*   Updated: 2022/06/22 21:16:00 by ijmari           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_free_list(t_returned_data *head)
{
	t_returned_data	*temp;

	while (head)
	{
		temp = head->next;
		ft_free(head->args);
		if (head->cmd_path)
			free(head->cmd_path);
		free(head);
		head = temp;
	}
}

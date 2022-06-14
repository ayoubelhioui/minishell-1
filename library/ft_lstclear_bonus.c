/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ijmari <ijmari@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/14 15:00:55 by ijmari            #+#    #+#             */
/*   Updated: 2022/06/14 15:00:56 by ijmari           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*temp;

	if (*lst && del)
	{
		temp = *lst;
		while (temp->next)
		{
			temp = *lst;
			ft_lstdelone(temp, del);
			*lst = (*lst)->next;
		}
	}
	*lst = 0;
}

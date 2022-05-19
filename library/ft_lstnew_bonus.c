/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ijmari <ijmari@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/09 14:02:23 by ijmari            #+#    #+#             */
/*   Updated: 2022/05/19 13:41:21 by ijmari           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_list	*ft_lstnew(void *content)
{
	t_list	*new;
	char	equ[2];
	char	*check;

	equ[0] = '=';
	equ[1] = '\0';
	check = (char *) content;
	new = (t_list *) malloc (sizeof(t_list));
	if (!new)
		return (0);
	if (ft_strstr(check, equ))
		new->criteria = 'e';
	else
		new->criteria = 'x';
	new->content = content;
	new->next = NULL;
	return (new);
}

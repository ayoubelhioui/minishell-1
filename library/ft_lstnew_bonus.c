/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-hiou <ael-hiou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/14 15:01:08 by ijmari            #+#    #+#             */
/*   Updated: 2022/06/29 15:22:35 by ael-hiou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_list	*ft_lstnew(char *content)
{
	t_list	*new;

	new = (t_list *) malloc (sizeof(t_list));
	if (!new)
		return (0);
	if (ft_strstr(content, "="))
		new->criteria = 'e';
	else
		new->criteria = 'x';
	new->content = ft_strdup(content);
	new->next = NULL;
	return (new);
}


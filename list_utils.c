/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ijmari <ijmari@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/27 15:21:58 by ijmari            #+#    #+#             */
/*   Updated: 2022/06/27 16:22:03 by ijmari           ###   ########.fr       */
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

t_list	*ft_lstdup(t_list *a)
{
	t_list	*dup;
	dup = ft_lstnew (a->content);
	a = a->next;
	while (a)
	{
		ft_lstadd_back (&dup, ft_lstnew(a->content));
		a = a->next;
	}
	return (dup);
}

void	set_oldpwd(t_list **env, char *old)
{
	t_list	*head;
	char	**pw;
	char	**prev;

	head = (*env);
	while (head)
	{
		pw = split_with_equ(head->content);
		if (!ft_strcmp(pw[0], "OLDPWD"))
		{
			ft_free(pw);
			break ;
		}
		ft_free(pw);
		head = head->next;
	}
	if (!head)
		return ;
	else if (g_key.cd_flag == 1)
	{
		prev = split_with_equ(old);
		if (head->content)
			free(head->content);	
		head->content = ft_strjoin("OLDPWD=", prev[1]);
		ft_free(prev);
	}
}

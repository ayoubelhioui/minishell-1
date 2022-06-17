/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ijmari <ijmari@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/14 14:58:47 by ijmari            #+#    #+#             */
/*   Updated: 2022/06/17 19:46:14 by ijmari           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	get_things_changed(char *arg, t_list **env)
{
	if (there_is_plus(arg))
		add_value (arg, env);
	else
		change_value(arg, env);
}

void	free_splits(char **first, char **second)
{
	ft_free(first);
	ft_free(second);
}

void	change_path_value(t_list **env)
{
	t_list	*head;
	char	**new;
	char	*cwd;
	char	*fr;

	head = *env;
	while (head)
	{
		new = split_with_equ(head->content);
		if (!ft_strcmp(new[0], "PWD"))
		{
			ft_free(new);
			break ;
		}
		ft_free(new);
		head = head->next;
	}
	if (!head)
		return ;
	else
	{
		cwd = getcwd(NULL, sizeof(cwd));
		// if (head->content)
		// 	free(head->content);
		fr = ft_strjoin("PWD=", cwd);
		head->content = fr;
		free(fr);
		free(cwd);
	}
}

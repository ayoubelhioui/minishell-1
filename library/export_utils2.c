/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ijmari <ijmari@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/14 14:58:47 by ijmari            #+#    #+#             */
/*   Updated: 2022/06/27 16:20:12 by ijmari           ###   ########.fr       */
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

void	set_new_path(t_list *head)
{
	char	*cwd;

	cwd = getcwd(NULL, sizeof(cwd));
	if (g_key.cd_flag == 0)
	{
		free(cwd);
		return ;
	}
	if (head->content)
		free(head->content);
	head->content = ft_strjoin("PWD=", cwd);
	free(cwd);
}

void	change_path_value(t_list **env)
{
	t_list	*head;
	char	**new;

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
		set_oldpwd(env, head->content);
		set_new_path(head);
	}
}

void	adding(char **spl, char **split_arg, t_list **env)
{
	char	*temp;

	if (spl[1] == NULL && split_arg[1])
	{
		if (!ft_equal((*env)->content))
		{
			temp = (*env)->content;
			(*env)->content = ft_strjoin((*env)->content, "=");
			free(temp);
		}
		temp = (*env)->content;
		(*env)->content = ft_strjoin((*env)->content, split_arg[1]);
		free(temp);
		(*env)->criteria = 'e';
	}
	else
	{
		temp = (*env)->content;
		(*env)->content = ft_strjoin((*env)->content, split_arg[1]);
		free(temp);
	}
}

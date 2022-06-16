/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_check.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-hiou <ael-hiou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/14 12:46:17 by ijmari            #+#    #+#             */
/*   Updated: 2022/06/14 16:28:16 by ael-hiou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	built_exist(t_returned_data *ret, t_list **env)
{
	if (!ft_strcmp(ret->cmd_path, "/usr/bin/cd"))
		return (1);
	else if (!ft_strcmp(ret->cmd_path, "/bin/pwd"))
		return (1);
	else if (!ft_strcmp(ret->cmd_path, "/usr/bin/env"))
		return (1);
	else if (!ft_strcmp(ret->cmd_path, "/bin/echo"))
		return (1);
	else if (!ft_strcmp(ret->cmd_path, "exit"))
		return (1);
	else if (!ft_strcmp(ret->cmd_path, "export"))
		return (1);
	else if (!ft_strcmp(ret->cmd_path, "unset"))
		return (1);
	return (0);
}

int	built_check(t_returned_data *ret, t_list **env)
{
	if (!ft_strcmp(ret->cmd_path, "/usr/bin/cd"))
		cd(&ret->args[1], env);
	else if (!ft_strcmp(ret->cmd_path, "/bin/pwd"))
		pwd();
	else if (!ft_strcmp(ret->cmd_path, "/usr/bin/env"))
		ft_env(env);
	else if (!ft_strcmp(ret->cmd_path, "/bin/echo"))
		ft_echo(&ret->args[1]);
	else if (!ft_strcmp(ret->cmd_path, "exit"))
	{
		if (ret->args[1])
		{
			key.exit_stat = atoi(ret->args[1]);
			ft_exit(ret->exit_stat);
		}
		else
			ft_exit(0);
	}
	else if (!ft_strcmp(ret->cmd_path, "export"))
		ft_export(env, &ret->args[1]);
	else if (!ft_strcmp(ret->cmd_path, "unset"))
		ft_unset(env, &ret->args[1]);
	else
		return (0);
	return (1);
}

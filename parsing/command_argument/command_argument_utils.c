/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_argument_utils.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-hiou <ael-hiou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/24 11:38:44 by ael-hiou          #+#    #+#             */
/*   Updated: 2022/06/27 19:02:52 by ael-hiou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "command_argument.h"

void	freeing(char **s)
{
	int		i;

	i = 0;
	while (s[i])
	{
		if (!ft_strcmp(s[i], "<") || !ft_strcmp(s[i], ">"))
		{
			free (s[i++]);
			if (!ft_strcmp(s[i], "<") || !ft_strcmp(s[i], ">"))
				free (s[i++]);
			free (s[i]);
		}
		i++;
	}
	free (s);
}

void	back_space(char *context)
{
	int	i;

	i = 0;
	while (context[i])
	{
		if (context[i] == -1)
			context[i] = SPACE;
		else if (context[i] == -2)
			context[i] = PIPE;
		i++;
	}
}

int	get_cmd_path_helper(t_cmd_path *vars)
{
	int	i;

	i = -1;
	while (vars->path[++i])
	{
		vars->temp1 = ft_strjoin(vars->path[i], "/");
		vars->full_path = ft_strjoin(vars->temp1, vars->temp);
		if (access(vars->full_path, F_OK) == 0)
		{
			free (vars->temp);
			free (vars->temp1);
			ft_free(vars->path);
			return (TRUE);
		}
		free(vars->temp1);
		free (vars->full_path);
	}
	return (FALSE);
}

char	*get_command_path(char **env_variables, char *command)
{
	t_cmd_path	vars;
	int			i;

	i = -1;
	while (env_variables[++i])
	{
		if (ft_strncmp(env_variables[i], "PATH", 4) == 0)
			break ;
		if (env_variables[i + 1] == NULL)
			return (NULL);
	}
	vars.path = ft_split(env_variables[i], ':');
	vars.temp = ft_strdup(command);
	if (get_cmd_path_helper(&vars))
		return (vars.full_path);
	ft_free(vars.path);
	return (vars.temp);
}

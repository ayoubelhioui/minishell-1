/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ijmari <ijmari@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/14 14:52:24 by ijmari            #+#    #+#             */
/*   Updated: 2022/06/24 16:08:09 by ijmari           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	checkand_deletion(t_list *curr, int pos, char *temp, t_list **env)
{
	char	**spl;
	char	*temp2;

	spl = split_with_equ(curr->content);
	temp2 = ft_strjoin(spl[0], "=");
	if (!ft_strcmp(temp, temp2))
	{
		delete_node(env, pos);
		ft_free(spl);
		free(temp2);
		return (1);
	}
	ft_free(spl);
	free(temp2);
	return (0);
}

int	check_unset(char *arg)
{
	int	i;

	i = 0;
	if (arg[0] >= '0' && arg[0] <= '9')
		return (0);
	while (arg[i])
	{
		if (!ft_isalnum(arg[i]) && arg[i] != '_')
			return (0);
		i++;
	}
	return (1);
}

void	handle_unset(t_list **env, char *arg)
{
	int		pos;
	char	*temp;
	t_list	*curr;

	g_key.exit_stat = 0;
	curr = *env;
	temp = ft_strjoin(arg, "=");
	pos = 0;
	while (curr)
	{
		if (checkand_deletion(curr, pos, temp, env))
			break ;
		pos++;
		curr = curr->next;
	}
	free(temp);
}

void	ft_unset(t_list **env, char	**args)
{
	t_list	*curr;
	char	*temp;
	int		i;
	int		pos;

	i = 0;
	if (!check_unset(args[i]) || args[i][0] == '=')
	{
		printf("unset: \'%s\': not a valid identifier\n", args[i]);
		g_key.exit_stat = 1;
		return ;
	}
	while (args[i])
		handle_unset(env, args[i++]);
}

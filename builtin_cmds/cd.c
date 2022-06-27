/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ijmari <ijmari@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/14 12:47:45 by ijmari            #+#    #+#             */
/*   Updated: 2022/06/27 14:57:41 by ijmari           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	cd(char **paths, t_list **env)
{
	int		ret;
	t_list	*curr;
	char	**data;

	curr = *env;
	ret = 0;
	g_key.cd_flag = 1;
	if (*paths == NULL || !ft_strcmp(paths[0], "~"))
	{
		while (curr)
		{
			data = split_with_equ(curr->content);
			if (!ft_strcmp(data[0], "HOME"))
			{
				ret = chdir((const char *) data[1]);
				ft_free(data);
				break ;
			}
			ft_free(data);
			curr = curr->next;
		}
	}
	else
		ret = chdir((const char *) paths[0]);
}

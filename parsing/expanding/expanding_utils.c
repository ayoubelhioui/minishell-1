/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expanding_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-hiou <ael-hiou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/24 10:14:54 by ael-hiou          #+#    #+#             */
/*   Updated: 2022/06/25 14:25:43 by ael-hiou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expanding.h"

char	*expanding_join(char *s1, char *s2)
{
	size_t	total_len;
	size_t	i;
	size_t	j;
	char	*str;

	i = 0;
	j = 0;
	total_len = ft_strlen(s1) + ft_strlen(s2);
	str = malloc((total_len + 1));
	if (!str)
		return (NULL);
	while (i < ft_strlen(s1))
	{
		str[i] = s1[i];
		i++;
	}
	while (j < ft_strlen(s2))
		str[i++] = s2[j++];
	str[i] = '\0';
	return (str);
}

void	get_value(t_dollar_sign_vars *vars, char **env)
{
	if (vars->to_be_expanded[0] == ZERO)
		vars->env_value = ft_strjoin(vars->temp1, vars->temp);
	else
		vars->env_value = search_in_env(vars->to_be_expanded, env);
}

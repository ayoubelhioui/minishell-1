/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   join_pl.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ijmari <ijmari@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/14 15:13:51 by ijmari            #+#    #+#             */
/*   Updated: 2022/06/14 15:13:55 by ijmari           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*join_pl(char const *s1, char const *s2)
{
	int		i;
	int		j;
	char	*new;
	int		ls1;
	int		ls2;

	if (!s1 || !s2)
		return (NULL);
	ls1 = ft_strlen(s1) - 1;
	ls2 = ft_strlen(s2);
	new = (char *) malloc ((ls1 + ls2 + 1));
	if (!new)
		return (NULL);
	i = 0;
	j = 0;
	while (i < ls1)
		new[i++] = s1[j++];
	j = 0;
	while (i < (ls1 + ls2))
		new[i++] = s2[j++];
	new[i] = '\0';
	return (new);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-hiou <ael-hiou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/14 15:12:46 by ijmari            #+#    #+#             */
/*   Updated: 2022/06/29 15:09:16 by ael-hiou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "library.h"

char	*ft_strdup(const char *src)
{
	size_t	n;
	size_t	i;
	char	*p;

	if (!src)
		return (NULL);
	n = ft_strlen(src);
	p = malloc(sizeof(char) * (n + 1));
	if (p)
	{
		i = 0;
		while (src[i])
		{
			p[i] = src[i];
			i++;
		}
		p[i] = '\0';
	}
	else
		return (0);
	return (p);
}

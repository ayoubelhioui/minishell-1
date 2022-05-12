/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   library.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/22 18:05:59 by marvin            #+#    #+#             */
/*   Updated: 2022/04/22 18:05:59 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBRARY_H
# define LIBRARY_H
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
char	    *ft_strtrim(char *s1, char *set);
char        **ft_split(char const *s, char c);
size_t	    ft_strlen(const char *s);
char	    *ft_strdup(const char *src);
size_t	    ft_strlcpy(char *dst, const char *src, size_t dstsize);
#endif
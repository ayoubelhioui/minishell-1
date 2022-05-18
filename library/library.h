/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   library.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ijmari <ijmari@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/22 18:05:59 by marvin            #+#    #+#             */
/*   Updated: 2022/05/18 12:31:44 by ijmari           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBRARY_H
# define LIBRARY_H
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
typedef struct s_list
{
	char			*content;
	struct s_list	*next;
}	t_list;
char	    *ft_strtrim(char *s1, char *set);
char        **ft_split(char const *s, char c);
size_t	    ft_strlen(const char *s);
char	    *ft_strdup(const char *src);
size_t	    ft_strlcpy(char *dst, const char *src, size_t dstsize);
void		ft_lstadd_back(t_list **lst, t_list *new);
int	ft_lstsize(t_list *lst);
t_list	*ft_lstnew(void *content);
t_list	*ft_lstlast(t_list *lst);
void	ft_lstdelone(t_list *lst, void (*del)(void *));
void	ft_lstadd_front(t_list **lst, t_list *new);
void	ft_lstadd_back(t_list **lst, t_list *new);
char	*ft_strjoin(char const *s1, char const *s2);
void	create_list(char **env, t_list **env_l);
#endif
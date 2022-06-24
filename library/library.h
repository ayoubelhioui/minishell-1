/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   library.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-hiou <ael-hiou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/14 15:14:17 by ijmari            #+#    #+#             */
/*   Updated: 2022/06/24 10:28:43 by ael-hiou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# ifndef LIBRARY_H
# define LIBRARY_H
# include <stdio.h>
# include <string.h>
# include <stdlib.h>
# include <unistd.h>
# include <ctype.h>

typedef struct s_list
{
	char			*content;
	int				value;
	char			criteria;
	struct s_list	*next;
}	t_list;

char		*copy(char const *s, char *str, unsigned int start, size_t len);
size_t		ft_strlcpy(char *dst, const char *src, size_t dstsize);
char		*ft_substr(char const *s, unsigned int start, size_t len);
char		*ft_strjoin(char *s1, char *s2);
char		*ft_strtrim(char *s1, char *set);
int			ft_strncmp(const char *s1, const char *s2, size_t n);
int			ft_strcmp(const char *s1, const char *s2);
char		**ft_split(char *s, char c);
int			ft_atoi(const char *str);
size_t		ft_strlen(const char *s);
char		*ft_strdup(const char *src);
int			ft_isdigit(int c);
int			ft_isalpha(int c);
int			ft_isalnum(int c);
void		ft_lstadd_back(t_list **lst, t_list *new);
int			ft_lstsize(t_list *lst);
t_list		*ft_lstnew(char	*content);
t_list		*ft_lstlast(t_list *lst);
void		ft_lstdelone(t_list *lst, void (*del)(void *));
void		ft_lstadd_front(t_list **lst, t_list *new);
void		ft_lstadd_back(t_list **lst, t_list *new);
void		create_list(char **env, t_list **env_l);
int			ft_strstr(const char *s1, const char *s2);
int			ft_check(const char *set, char a);
size_t		ft_right(const char *s1, const char *set);
size_t		ft_left(const char *s1, const char *set);
char		*ft_strtrim(char *s1, char *set);
void		print_list(t_list *en, char *arg);
void		ft_free(char **ptr);
char		*join_pl(char const *s1, char const *s2);
char		**split_with_plus(char *arg);
int			there_is_plus(char *arg);
void		sort_list(t_list *en);
void		swap(t_list *a, t_list *b, int *ptr);
int			check_if_valid(char *arg);
void		add_it_back(char **split_arg, char *arg, t_list **env);
char		**split_with_equ(char *arg);
void		change_path_value(t_list **env);
void		free_splits(char **first, char **second);
void		get_things_changed(char *arg, t_list **env);
void		add_value(char *arg, t_list **env);
void		change_value(char *arg, t_list **env);
void		adding(char **spl, char **split_arg, t_list **env);
#endif
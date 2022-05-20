#ifndef LIBRARY_H
# define LIBRARY_H
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
typedef struct s_list
{
	char			*content;
	char			criteria;
	struct s_list	*next;
}	t_list;
char	    *copy(char const *s, char *str, unsigned int start, size_t len);
size_t	    ft_strlcpy(char *dst, const char *src, size_t dstsize);
char	    *ft_substr(char const *s, unsigned int start, size_t len);
char	    *ft_strjoin(char const *s1, char const *s2);
char	    *ft_strtrim(char *s1, char *set);
int	        ft_strncmp(const char *s1, const char *s2, size_t n);
int	        ft_strcmp(const char *s1, const char *s2);
char        **ft_split(char const *s, char c);
size_t	    ft_strlen(const char *s);
char	    *ft_strdup(const char *src);
int	        ft_isdigit(int c);
int	        ft_isalpha(int c);
int	        ft_isalnum(int c);
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
#endif
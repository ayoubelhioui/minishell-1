#include "../minishell.h"

t_list	*ft_lstnew(char *content)
{
	t_list	*new;
	char	*temp;

	new = (t_list *) malloc (sizeof(t_list));
	if (!new)
		return (0);
	// printf("content is %s\n", content);
	if (ft_strstr(content, "="))
		new->criteria = 'e';
	else
		new->criteria = 'x';
	new->content = content;
	new->next = NULL;
	return (new);
}

#include "../minishell.h"

t_list	*ft_lstnew(char *content)
{
	t_list	*new;

	new = (t_list *) malloc (sizeof(t_list));
	if (!new)
		return (0);
	printf("%s and %d\n", content, ft_strstr(content, "=\0"));
	if (ft_strstr(content, "=\0"))
		new->criteria = 'e';
	else
		new->criteria = 'x';
	new->content = content;
	new->next = NULL;
	return (new);
}

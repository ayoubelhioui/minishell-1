#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*temp;

	if (*lst && del)
	{
		temp = *lst;
		while (temp->next)
		{
			temp = *lst;
			ft_lstdelone(temp, del);
			*lst = (*lst)->next;
		}
	}
	*lst = 0;
}

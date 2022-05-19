#include "../minishell.h"

void	ft_env(t_list **env)
{
	t_list *current;

	current = *env;
	while (current != 0)
	{
		if (current->criteria == 'e')
			printf("%s\n", current->content);
		current = current->next;
	}
}

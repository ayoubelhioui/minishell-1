#include "../minishell.h"

void	ft_export(t_list **env, char **args)
{
	int	i = 0;
	while (args[i])
	{
		ft_lstadd_back(env, ft_lstnew(args[i]));
		i++;
	}
}
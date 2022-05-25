#include "../minishell.h"

void	ft_unset(t_list **env, char	**args)
{
	t_list	*curr;
	char	*temp;
	int		i;
	int		pos;

	i = 0;
	while (args[i])
	{
		curr = *env;
		temp = ft_strjoin(args[i], "=");
		pos = 0;
		while (curr)
		{
			if (ft_strstr(curr->content, temp) || ft_strstr(curr->content, args[i]))
			{
				delete_node(env, pos);
				break;
			}
			pos++;
			curr = curr->next;
		}
		free(temp);
		i++;
	}
}
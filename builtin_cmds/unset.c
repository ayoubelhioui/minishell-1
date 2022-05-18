#include "../minishell.h"

void	ft_unset(t_list **env, char	**args)
{
	t_list	*curr;
	char	*temp;
	char	equ[2];
	int		i;
	int		pos;

	i = 0;
	equ[0] = '=';
	equ[1] = '\0';
	while (args[i])
	{
		curr = *env;
		temp = ft_strjoin(args[i], equ);
		pos = 0;
		while (curr)
		{
			if (ft_strstr(curr->content, temp))
			{
				delete_node(env, curr, pos);
				break;
			}
			pos++;
			curr = curr->next;
		}
		free(temp);
		i++;
	}
}
#include "../minishell.h"

int	checkand_deletion(t_list *curr, int pos, char *temp, t_list **env)
{
	char	**spl;
	char	*temp2;

	spl = split_with_equ(curr->content);
	temp2 = ft_strjoin(spl[0], "=");
	if (!ft_strcmp(temp, temp2))
	{
		delete_node(env, pos);
		return (1);
	}
	return (0);
}
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
			if (checkand_deletion(curr, pos, temp, env))
				break;
			pos++;
			curr = curr->next;
		}
		free(temp);
		i++;
	}
}
#include "minishell.h"

int	is_int(char *str)
{
	int	i;
	int	negative;

	i = 0;
	negative = 0;
	if (str[i] == '-')
		i++;
	while (str[i])
	{
		if (!(str[i] >= '0' && str[i] <= '9'))
			return (0);
		i++;
	}
	return (1);
}

void	create_list(char **env, t_list **env_l)
{
	int	i;

	i = 0;
	*env_l = ft_lstnew (env[i]);
	i++;
	while (env[i])
		ft_lstadd_back (env_l, ft_lstnew(env[i++]));
}

void	delete_node(t_list **env, t_list *node, int pos)
{
	t_list	*del;
	t_list	*original;
	int		i;

	i = 0;
	original = *env;
	if (pos == 0 && original == node)
	{
		*env = (*env)->next;
		original->next = NULL; 
	}
	else
	{
		while (i < pos - 1)
		{
			i++;
			original = original->next;
		}
		del = original->next;
		original->next = original->next->next;
		del->next = NULL;
		free(del);
	}
}

void	print_list(t_list *en)
{
	while (en)
    {
        printf("declare -x %s\n", en->content);
        en = en->next;
    }
}

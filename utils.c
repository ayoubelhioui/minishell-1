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

void	delete_node(t_list **env, int pos)
{
	t_list	*del;
	t_list	*original;
	int		i;

	i = 0;
	original = *env;
	if (pos == 0)
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

void	ft_free(char **ptr)
{
	int i;

	i = 0;
	while (ptr[i])
		free(ptr[i++]);
	free(ptr);
}

void	print_list(t_list *en, char	*arg)
{
	char	**name_path;

	while (en)
    {
		name_path = ft_split(en->content, '=');
		if (en->criteria == 'e')
        	printf("declare -x %s%c\"%s\"\n", name_path[0], '=', name_path[1]);
		else
			printf("declare -x %s\n", name_path[0]);
		ft_free(name_path);
        en = en->next;
    }
}
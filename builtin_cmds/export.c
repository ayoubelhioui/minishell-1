#include "../minishell.h"

int	existed(char *arg, t_list **env, char **split_arg)
{
	t_list	*curr;
	int		flag;
	int 	i;
	char	**spl;

	i = 0;
	flag = 0;
	while (arg[i])
	{
		if (arg[i] == '=')
			flag = 1;
		if (arg[i] == '+' && flag == 0 && arg[i + 1] == '=')
			return (0);
		i++;
	}
	curr = *env;
	while (curr)
	{
		spl = ft_split(curr->content, '=');
		if (!ft_strcmp(arg, curr->content)
		|| (ft_equal(curr->content) && ft_strcmp(curr->content, arg))
		|| (!ft_equal(curr->content) && ft_strcmp(spl[0], arg)))
			return (1);
		curr = curr->next;
	}
	return (0);
}

void swap(t_list *a, t_list *b)
{
    char *temp;
	char crit;

    temp = a->content;
	crit = a->criteria;
	a->content = b->content;
	a->criteria = b->criteria;
	b->content = temp;
	b->criteria = crit;
}

void sort_list(t_list *en)
{
    int swapped = 1;
    t_list *ptr1;
    t_list *lptr;
	t_list *curr;

	curr = en;
	lptr = NULL;
    if (en == NULL)
        return;
    while(swapped)
    {
        swapped = 0;
        ptr1 = curr;
        while (ptr1->next != lptr)
        {
            if (ft_strcmp(ptr1->content , ptr1->next->content) > 0)
            { 
                swap(ptr1, ptr1->next);
                swapped = 1;
            }
            ptr1 = ptr1->next;
        }
        lptr = ptr1;
    }
	print_list(en, NULL);
}

int	check_if_valid(char *arg)
{
	int i;
	int	equal;
	int	flag;

	equal = 0;
	flag = 0;
	i = 0;
	while (arg[i])
	{
		if ((arg[i] == '+' && equal == 0 && arg[i + 1] != '=')
		|| (arg[i] == '-' && equal == 0))
			return (0);
		else if (arg[i] == '=')
			equal = 1;
		i++;
	}
	i = 0;
	while (arg[i])
	{
		if (!ft_isalnum(arg[i]) && arg[i] != '=' && arg[i] != '+')
			return (0);
		i++;
	}
	return (1);
}
void	ft_export(t_list **env, char **args)
{
	int		i;
	t_list	*ret;
	t_list	*curr;
	t_list	*presence_case;
	char	**split_arg;
	char	**sorted_env;
	char	*check;
	int		len;
	int		j;

	i = 0;
	curr = *env;
	if (*args == NULL)
		sort_list(*env);
	while (args[i])
	{
		split_arg = ft_split(args[i], '=');
		// ret = check_diff(env, args[i], split_arg);
		if (!check_if_valid(args[i]))
		{
			printf ("export: \'%s\': not a valid identifier\n", args[i]);
			i++;
			continue;
		}
		if (existed(args[i], env, split_arg))
		{
			i++;
			continue;
		}
		// else if (ret)
		// {
		// 	len = ft_strlen(args[i]);
		// 	ret->content = malloc((len + 1) * sizeof(char));
		// 	j = 0;
		// 	while (j < len)
		// 	{
		// 		ret->content[j] = args[i][j];
		// 		j++;
		// 	}
		// 	ret->content[j] = '\0';
		// }
		else
			ft_lstadd_back(env, ft_lstnew(args[i]));
		i++;
	}
}
#include "../minishell.h"

t_list	*check_presence(t_list **env, char **split_arg, char *arg)
{
	t_list	*curr;
	char	*temp;

	curr = *env;
	if (split_arg[1] != NULL)
		temp = ft_strjoin(split_arg[0], "=");
	while (curr)
	{
		if (!split_arg[1])
		{
			if (!ft_strcmp(arg, curr->content))
				return (curr);
		}
		else
		{
			if (ft_strstr(curr->content, temp))
				return (curr);
		}
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
	if (!ft_strstr(arg, "="))
		return (1);
	while (arg[i])
	{
		if ((arg[i] == '+' && equal == 0 && arg[i + 1] != '=')
		|| (arg[i] == '-' && equal == 0))
			return (0);
		else if (arg[i] == '=')
			equal = 1;
		i++;
	}
	while (arg[i])
	{
		if (arg[i] == '+' && arg[i] == '=')
			return (2);
		i++;
	}
	return (1);
}
void	ft_export(t_list **env, char **args)
{
	int		i;
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
		if (!check_if_valid(args[i]))
		{
			printf ("export: \'%s\': not a valid identifier\n", args[i]);
			i++;
			continue;
		}
		else if (check_if_valid(args[i]) == 2)
		{

		}
		else if (check_presence(env, split_arg, args[i]))
		{
			i++;
			continue;
		}
		else
			ft_lstadd_back(env, ft_lstnew(args[i]));
		i++;
	}
}
#include "../minishell.h"

void	add_it_back(char **split_arg, char *arg, t_list **env)
{
	char	*temp;

	temp = NULL;
	if (there_is_plus(arg))
	{
		printf("HERE 4\n");
		temp = join_pl(split_arg[0], "=");
		temp = ft_strjoin(temp, split_arg[1]);
		printf("HERE 4 %s and %s\n", split_arg[0], split_arg[1]);
		ft_lstadd_back(env, ft_lstnew(temp));
	}
	else
	{
		printf("HERE 5 %s and %s\n", split_arg[0], split_arg[1]);
		ft_lstadd_back(env, ft_lstnew(arg));
	}
}

int	check_if_valid(char *arg)
{
	int i;
	int	equal;
	int	flag;

	equal = 0;
	flag = 0;
	i = 0;
	if (arg[0] >= '0' && arg[0] <= '9')
		return (0);
	while (arg[i] && arg[i] != '=')
	{
		if ((arg[i] == '+' && equal == 0 && arg[i + 1] != '=')
		|| (arg[i] == '-' && equal == 0))
			return (0);
		else if (arg[i] == '=')
			equal = 1;
		i++;
	}
	i = 0;
	while (arg[i] && arg[i] != '=')
	{
		if (!ft_isalnum(arg[i]) && arg[i] != '=' && arg[i] != '+' && arg[i] != '_')
			return (0);
		i++;
	}
	return (1);
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

int	there_is_plus(char *arg)
{
	int	i;

	i = 0;
	while (arg[i])
	{
		if (arg[i] == '+' && arg[i + 1] == '=')
			return (1);
		i++;
	}
	return (0);
}
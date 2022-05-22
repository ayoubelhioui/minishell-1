#include "../minishell.h"


int	change_value(char *arg, t_list **env, char **split_arg)
{
	int len;
	int	j;
	t_list	*curr;
	char	**spl;

	return (0);
}

t_list	*existed(char *arg, t_list **env, char **split_arg)
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
		if (!ft_strcmp(spl[0] ,split_arg[0]) && spl[1] == NULL && split_arg[1] == NULL)
			return (0);
		else if (spl[1] != NULL && split_arg[1]!= NULL
		&& !ft_strcmp(spl[0] ,split_arg[0]) && !ft_strcmp(spl[1] ,split_arg[1]))
			return (0);
		else if (!ft_strcmp(spl[0] ,split_arg[0]) && split_arg[1] == NULL)
			return (0);
		ft_free(spl);
		curr = curr->next;
	}
	return (curr);
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
		ret = existed(args[i], env, split_arg);
		if (!check_if_valid(args[i]))
		{
			printf ("export: \'%s\': not a valid identifier\n", args[i]);
			i++;
			continue;
		}
		if (!ret)
		{
			printf("OK\n");
			i++;
			continue;
		}
		else if (ret)
		{
			printf("OKKK\n");
			change_value(args[i], env, split_arg);
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
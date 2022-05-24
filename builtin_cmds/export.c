#include "../minishell.h"


void	change_value(char *arg, t_list **env)
{
	t_list	*curr;
	char	**spl;
	char	**split_arg;
	int		len;
	int		j;

	curr = *env;
	while (*env)
	{
		spl = ft_split((*env)->content, '=');
		split_arg = ft_split(arg, '=');
		if (!ft_strcmp(spl[0], split_arg[0]))
		{
			len = ft_strlen(arg);
			(*env)->content = malloc((len + 1));
			j = 0;
			while (arg[j])
			{
				(*env)->content[j] = arg[j];
				j++;
			}
			(*env)->content[j] = '\0';
			(*env)->criteria = 'e';
		}
		(*env) = (*env)->next; 
	}
	*env = curr;
}

void	add_value(char *arg, t_list **env)
{
	t_list	*curr;
	char	**spl;
	char	**split_arg;
	
	curr = *env;
	while (*env)
	{
		spl = ft_split((*env)->content, '=');
		split_arg = split_env(arg);
		if (!ft_strcmp(spl[0], split_arg[0]))
		{
			if (spl[1] == NULL && split_arg[1])
			{
				(*env)->content = ft_strjoin((*env)->content, "=");
				(*env)->content = ft_strjoin((*env)->content, split_arg[1]);
				(*env)->criteria = 'e';
			}
			else
				(*env)->content = ft_strjoin((*env)->content, split_arg[1]);
		}
		ft_free(spl);
		(*env) = (*env)->next;
	}
	*env = curr;
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
int	ft_isnode(t_list **env, char *arg)
{
	t_list	*curr;
	char	**spl;
	char	**split_arg;
	int		check;

	curr = *env;
	check = there_is_plus(arg);
	while (curr)
	{
		spl = ft_split(curr->content, '=');
		if (check)
			split_arg = ft_split(arg, '+');
		else
			split_arg = ft_split(arg, '=');
		if (!ft_strcmp(spl[0], split_arg[0]))
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
void	ft_export(t_list **env, char **args)
{
	int		i;
	t_list	*ret;
	t_list	*curr;
	t_list	*presence_case;
	char	**split_arg;
	char	**sorted_env;
	char	*check;
	char	*temp;
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
			printf("export: \'%s\': not a valid identifier\n", args[i]);
			i++;
			continue;
		}
		else if (ft_isnode(env, args[i]))
		{
			printf("HERE there is\n");
			if (there_is_plus(args[i]))
			{
				printf("HERE add value\n");
				add_value (args[i], env);
			}
			else
				change_value(args[i], env);
		}
		else
		{
			if (there_is_plus(args[i]))
			{
				printf("HERE add new value with +\n");
				temp = join_pl(split_arg[0], "=");
				temp = ft_strjoin(temp, split_arg[1]);
				ft_lstadd_back(env, ft_lstnew(temp));
			}
			else
			{
				printf("HERE add normally\n");
				ft_lstadd_back(env, ft_lstnew(args[i]));
			}
		}	
		i++;
	}
}
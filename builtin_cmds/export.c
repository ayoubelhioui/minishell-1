#include "../minishell.h"

t_list	*find_the_arg(t_list **env, char *arg, char **split_arg, char *equ)
{
	t_list	*curr;
	char	*searched;
	int		i;

	searched = ft_strjoin(split_arg[0], equ);
	curr = *env;
	while (curr)
	{
		if (ft_strstr(curr->content, searched))
		{
			free(searched);
			return (curr);
		}
		curr = curr->next;
	}
	return (0);
}

void swap(t_list *a, t_list *b)
{
    char *temp;

    temp = a->content;
    a->content = b->content;
    b->content = temp;
}

void sort_list(t_list *en)
{
    int swapped = 1;
    t_list *ptr1;
    t_list *lptr;

	lptr = NULL;
    if (en == NULL)
        return;
    while(swapped)
    {
        swapped = 0;
        ptr1 = en;

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
void	ft_export(t_list **env, char **args)
{
	int		i;
	char	equ[2];
	t_list	*curr;
	t_list	*presence_case;
	char	**split_arg;
	char	**sorted_env;
	int		len;
	int		j;

	i = 0;
	equ[0] = '=';
	equ[1] = '\0';
	if (*args == NULL)
		sort_list(*env);
	while (args[i])
	{
		split_arg = ft_split(args[i], '=');
		presence_case = find_the_arg(env, args[i], split_arg, equ);
		if (presence_case)
		{
			len = ft_strlen(args[i]);
			presence_case->content = malloc((len + 1) * sizeof(char));
			j = 0;
			while (j < len)
			{
				presence_case->content[j] = args[i][j];
				j++;
			}
			presence_case->content[j] = '\0';
		}
		else
			ft_lstadd_back(env, ft_lstnew(args[i]));
		ft_free(split_arg);
		i++;
	}
}
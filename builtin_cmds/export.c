#include "../minishell.h"


void	change_value(char *arg, t_list **env)
{
	t_list	*curr;
	char	**spl;
	char	**split_arg;
	int		len;
	int		j;
	int		k = 0;

	curr = *env;
	while (*env)
	{
		spl = split_with_equ((*env)->content);
		split_arg = split_with_equ(arg);
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
		k++;
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
		spl = split_with_equ((*env)->content);
		split_arg = split_with_plus(arg);
		printf("HERE 5 args %s and %s and spl %s and %s\n", split_arg[0], split_arg[1], spl[0], spl[1]);
		if (!ft_strcmp(spl[0], split_arg[0]))
		{
			if (spl[1] == NULL && split_arg[1])
			{
				(*env)->content = ft_strjoin((*env)->content, "=");
				(*env)->content = ft_strjoin((*env)->content, split_arg[1]);
				(*env)->criteria = 'e';
				printf("WAS HERE 1 %s\n", (*env)->content);
			}
			else
				(*env)->content = ft_strjoin((*env)->content, split_arg[1]);
		}
		ft_free(spl);
		(*env) = (*env)->next;
	}
	*env = curr;
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
		spl = split_with_equ(curr->content);
		if (check)
			split_arg = split_with_plus(arg);
		else
			split_arg = split_with_equ(arg);
		if (!ft_strcmp(spl[0], split_arg[0]))
			return (1);
		curr = curr->next;
	}
	return (0);
}

void	ft_export(t_list **env, char **args)
{
	int		i;
	char	**split_arg;

	i = 0;
	if (*args == NULL)
		sort_list(*env);
	while (args[i])
	{
		split_arg = split_with_equ(args[i]);
		if (!check_if_valid(args[i]))
		{
			printf("export: \'%s\': not a valid identifier\n", args[i]);
			i++;
			continue;
		}
		else if (ft_isnode(env, args[i]))
		{
			if (there_is_plus(args[i]))
			{
				printf("HERE 1\n");
				add_value (args[i], env);
			}
			else
			{
				printf("HERE 2\n");
				change_value(args[i], env);
			}
		}
		else
			add_it_back(split_arg, args[i], env);	
		i++;
	}
}
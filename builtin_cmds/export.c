#include "../minishell.h"

void	changing(t_list **env, char *arg)
{
	int		len;
	int		j;

	len = ft_strlen(arg);
	(*env)->content = malloc(len + 1);
	j = 0;
	while (arg[j])
	{
		(*env)->content[j] = arg[j];
		j++;
	}
	(*env)->content[j] = '\0';
	(*env)->criteria = 'e';
}
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
		spl = split_with_equ((*env)->content);
		split_arg = split_with_equ(arg);
		if (!ft_strcmp(spl[0], split_arg[0]))
			changing(env, arg);
		ft_free(spl);
		ft_free(split_arg);
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
		spl = split_with_equ((*env)->content);
		split_arg = split_with_plus(arg);
		if (!ft_strcmp(spl[0], split_arg[0]))
		{
			if (spl[1] == NULL && split_arg[1])
			{
				if (!ft_equal((*env)->content))
					(*env)->content = ft_strjoin((*env)->content, "=");
				(*env)->content = ft_strjoin((*env)->content, split_arg[1]);
				(*env)->criteria = 'e';
			}
			else
				(*env)->content = ft_strjoin((*env)->content, split_arg[1]);
		}
		ft_free(spl);
		ft_free(split_arg);
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
	int k = 0;
	while (curr)
	{
		spl = split_with_equ(curr->content);
		if (check)
			split_arg = split_with_plus(arg);
		else
			split_arg = split_with_equ(arg);
		if (!ft_strcmp(spl[0], split_arg[0]))
		{
			ft_free(spl);
			ft_free(split_arg);
			return (1);
		}
		curr = curr->next;
		ft_free(spl);
		ft_free(split_arg);
	}
	return (0);
}

void	change_path_value(t_list **env)
{
	t_list *temp;
	char	**new;
	temp = *env;
	while (!ft_strstr(temp->content, "PWD="))
		temp = temp->next;
	if (!temp)
		return ;
	else
	{
		new = split_with_equ(temp->content);
		
	}
}
void	ft_export(t_list **env, char **args)
{
	int		i;
	char	**split_arg;

	i = 0;
	change_path_value(env);
	if (*args == NULL)
		sort_list(*env);
	while (args[i])
	{
		split_arg = split_with_equ(args[i]);
		if (!check_if_valid(args[i]) || args[i][0] == '=')
		{
			printf("export: \'%s\': not a valid identifier\n", args[i]);
			i++;
			continue;
		}
		else if (ft_isnode(env, args[i]))
		{
			if (there_is_plus(args[i]))
				add_value (args[i], env);
			else
				change_value(args[i], env);
		}
		else
			add_it_back(split_arg, args[i], env);
		ft_free(split_arg);
		i++;
	}
}
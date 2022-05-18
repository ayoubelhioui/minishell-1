#include "../minishell.h"

t_list	*find_the_arg(t_list **env, char *arg, char **split_arg)
{
	t_list	*curr;
	char	*searched;
	char	equ[2];
	int		i;

	equ[0] = '=';
	equ[1] = '\0';
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
void	ft_export(t_list **env, char **args)
{
	int		i;
	t_list	*curr;
	t_list	*presence_case;
	char	**split_arg;
	int		len;
	int		j;

	i = 0;
	if (*args == NULL)
	{
		curr = (*env);
		while (curr)
		{
			printf("declare -x %s\n", curr->content);
			curr = curr->next;
		}
	}
	while (args[i])
	{
		split_arg = ft_split(args[i], '=');
		presence_case = find_the_arg(env, args[i], split_arg);
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
		i++;
	}
}
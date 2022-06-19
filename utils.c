/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-hiou <ael-hiou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/14 16:35:49 by ijmari            #+#    #+#             */
/*   Updated: 2022/06/19 12:24:13 by ael-hiou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
	int		i;
	t_list	*head;

	i = 0;
	head = *env_l;
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

void	print_list(t_list *en, char	*arg)
{
	char	**name_path;
	t_list	*cc;

	cc = en;
	while (cc)
	{
		name_path = split_with_equ(cc->content);
		if (cc->criteria == 'e')
		{
			if (!ft_strcmp("\"\"", name_path[1]))
				printf("declare -x %s%c%s\n", name_path[0], '=', name_path[1]);
			else if (name_path[1])
				printf("declare -x %s%c\"%s\"\n", name_path[0], '=', name_path[1]);
			else
				printf("declare -x %s%c\"\"\n", name_path[0], '=');
		}
		else
			printf("declare -x %s\n", name_path[0]);
		ft_free(name_path);
		cc = cc->next;
	}
}

int	ft_equal(char *arg)
{
	int	i;

	i = 0;
	while (arg[i])
	{
		if (arg[i] == '=')
			return (1);
		i++;
	}
	return (0);
}


void	ft_free_list(t_returned_data *head)
{
	t_returned_data	*temp;

	while (head)
	{
		temp = head->next;
		ft_free(head->args);
		// free(head->cmd_dup);
    	free(head->cmd_path);
		free(head);
		head = temp;
	}
}
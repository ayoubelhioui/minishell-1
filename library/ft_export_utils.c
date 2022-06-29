/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ijmari <ijmari@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/14 16:02:27 by ijmari            #+#    #+#             */
/*   Updated: 2022/06/29 16:41:24 by ijmari           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	add_it_back(char **split_arg, char **arg, t_list **env, int i)
{
	char	*temp;

	temp = NULL;
	if (there_is_plus(arg[i]))
	{
		temp = join_pl(split_arg[0], "=");
		temp = ft_strjoin(temp, split_arg[1]);
		ft_lstadd_back(env, ft_lstnew(temp));
	}
	else
		ft_lstadd_back(env, ft_lstnew(arg[i]));
	if (arg[i + 1] == NULL)
		g_key.cd_flag = 0;
}

int	check_if_valid(char *arg)
{
	int	i;
	int	equal;

	equal = 0;
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
		if (!ft_isalnum(arg[i]) && arg[i] != '=' \
		&& arg[i] != '+' && arg[i] != '_')
			return (0);
		i++;
	}
	return (1);
}

void	swap(t_list *a, t_list *b, int *swapped)
{
	char	*temp;
	char	crit;

	temp = a->content;
	crit = a->criteria;
	a->content = b->content;
	a->criteria = b->criteria;
	b->content = temp;
	b->criteria = crit;
	*swapped = 1;
}

void	sort_list(t_list *en)
{
	int		swapped;
	t_list	*ptr1;
	t_list	*lptr;
	t_list	*curr;
	t_list	*lst_dup;

	lst_dup = ft_lstdup(en);
	swapped = 1;
	curr = lst_dup;
	lptr = NULL;
	if (lst_dup == NULL)
		return ;
	while (swapped)
	{
		swapped = 0;
		ptr1 = curr;
		while (ptr1->next != lptr)
		{
			if (ft_strcmp(ptr1->content, ptr1->next->content) > 0)
				swap(ptr1, ptr1->next, &swapped);
			ptr1 = ptr1->next;
		}
		lptr = ptr1;
	}
	print_list(lst_dup);
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

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-hiou <ael-hiou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/24 12:10:36 by ael-hiou          #+#    #+#             */
/*   Updated: 2022/06/24 13:31:30 by ael-hiou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_strcpy(char *s, char *str, int start_position, int length)
{
	int	i;

	i = 0;
	while (i < length)
	{
		s[i] = str[start_position];
		i++;
		start_position++;
	}
	s[i] = '\0';
}

int	redirection_counter(t_list *splitted_data, char redirection)
{
	int		i;
	int		counter;
	t_list	*temp;

	i = 0;
	counter = 0;
	temp = splitted_data;
	while (temp)
	{
		if (((ft_strlen(temp->content)) == 1) \
				&& (temp->content[0] == redirection))
			counter++;
		temp = temp->next;
	}
	return (counter);
}

char	*search_in_env(char *entered_data, char **env)
{
	int		i;
	char	**holder;
	char	*returned;

	i = 0;
	if (ft_isdigit(entered_data[0]))
		return (ft_strdup(entered_data + 1));
	while (env[i])
	{
		holder = ft_split(env[i], EQUAL);
		if (ft_strcmp(holder[0], entered_data) == 0)
		{
			returned = ft_strdup(holder[1]);
			ft_free(holder);
			return (returned);
		}
		ft_free(holder);
		i++;
	}
	return (ft_strdup(""));
}

void	all_about_free(char *s1, char *s2, char *s3)
{
	free (s1);
	free (s2);
	free (s3);
}

char	**get_new_env(t_list *env)
{
	int		length;
	int		i;
	char	**new_env;

	length = ft_lstsize(env);
	new_env = malloc(sizeof(char *) * (length + 1));
	i = 0;
	while (env)
	{
		new_env[i] = env->content;
		env = env->next;
		i++;
	}
	new_env[i] = NULL;
	return (new_env);
}

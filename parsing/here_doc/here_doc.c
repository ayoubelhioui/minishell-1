/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ijmari <ijmari@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/24 11:09:13 by ael-hiou          #+#    #+#             */
/*   Updated: 2022/06/28 14:46:46 by ijmari           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "here_doc.h"

int	find_heredoc_position(char **s)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (!ft_strcmp(s[i], "<"))
		{
			i++;
			if (!ft_strcmp(s[i], "<"))
			{
				if (!s[i + 2])
					return (TRUE);
			}
		}
		i++;
	}
	return (FALSE);
}

int	here_doc_helper2(t_here_doc_vars *vars, char *limiter)
{
	if (vars->s)
	{
		if (vars->entered_data)
			free(vars->entered_data);
		vars->entered_data = vars->s;
		return (FALSE);
	}
	else
	{
		if (g_key.flag == 6)
			printf(">\n");
		free (limiter);
		free (vars->entered_data);
		close(vars->p[STD_OUTPUT]);
		if (g_key.flag == 6)
			return (-4);
		return (TRUE);
	}
}

int	here_doc_helper(t_here_doc_vars *vars, char *limiter, char **env)
{
	int		value;
	char	*s;

	while (vars->entered_data)
	{
		if (!ft_strcmp(vars->entered_data, limiter))
			break ;
		s = expanding_here_doc(vars->entered_data, env);
		write(vars->p[STD_OUTPUT], s, ft_strlen(s));
		write(vars->p[STD_OUTPUT], "\n", 2);
		vars->entered_data = NULL;
		free(s);
		vars->s = readline("> ");
		value = here_doc_helper2(vars, limiter);
		if (value == -4)
			return (-4);
		else if (value == 1)
			return (vars->p[STD_INPUT]);
	}
	close(vars->p[STD_OUTPUT]);
	if (vars->entered_data)
		free (vars->entered_data);
	free (limiter);
	return (vars->p[STD_INPUT]);
}

int	here_doc(char *limiter, char **env)
{
	t_here_doc_vars	vars;

	g_key.flag_for_here = 1;
	pipe(vars.p);
	vars.s = readline("> ");
	if (vars.s)
		vars.entered_data = vars.s;
	else
	{
		if (g_key.flag == 6)
		{
			printf(">\n");
			return (-4);
		}
		close(vars.p[STD_OUTPUT]);
		return (vars.p[STD_INPUT]);
	}
	limiter = remove_quotes(limiter);
	return (here_doc_helper(&vars, limiter, env));
}

int	heredoc_searcher(char **splitted_data, t_returned_data \
*returned_data, char **env)
{
	int	i;
	int	in_quote;

	i = 0;
	in_quote = 0;
	while (splitted_data[i])
	{
		if (!ft_strcmp(splitted_data[i], "|"))
			returned_data = returned_data->next;
		else if (!ft_strcmp(splitted_data[i], "\""))
			in_a_quote(&in_quote, DOUBLE_QUOTE);
		else if (!ft_strcmp(splitted_data[i], "'"))
			in_a_quote(&in_quote, SINGLE_QUOTE);
		else if (!ft_strcmp(splitted_data[i], "<") \
		&& !ft_strcmp(splitted_data[i + 1], "<") && in_quote == 0)
		{
			i += 2;
			returned_data->input_fd = here_doc(splitted_data[i], env);
			g_key.flag_for_here = 0;
			if (returned_data->input_fd == -4)
				return (-4);
		}
		i++;
	}
	return (1);
}

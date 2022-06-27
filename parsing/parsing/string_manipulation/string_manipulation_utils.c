/* ************************************************************************** */
/*		                                                                    */
/*                                                        :::      ::::::::   */
/*   string_manipulation_utils.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-hiou <ael-hiou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/24 11:51:32 by ael-hiou          #+#    #+#             */
/*   Updated: 2022/06/24 17:32:38 by ael-hiou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "string_manipulation.h"

int	get_length(char **args)
{
	int	i;

	i = 0;
	while (args[i])
	i++;
	return (i);
}

void	replacing_space(t_data *entered_data, char quote)
{
	entered_data->index++;
	while (entered_data->context[entered_data->index] && \
	entered_data->context[entered_data->index] != quote)
	{
		if (entered_data->context[entered_data->index] == ' ')
			entered_data->context[entered_data->index] = -1;
		else if (entered_data->context[entered_data->index] == PIPE)
			entered_data->context[entered_data->index] = -2;
		entered_data->index++;
	}
}

void	quotes_counter(char *context, int *start, char quote, int *counter)
{
	*start += 1;
	while (context[*start] && context[*start] != quote)
	{
		*start += 1;
		*counter += 1;
	}
}

void	remove_quotes_helper(char *context, t_remove_quotes_vars *vars)
{
	while (context[vars->i])
	{
		if (context[vars->i] == DOUBLE_QUOTE)
		{
			vars->i++;
			while (context[vars->i] && context[vars->i] != DOUBLE_QUOTE)
				vars->new_string[vars->j++] = context[vars->i++];
		}
		else if (context[vars->i] == SINGLE_QUOTE)
		{
			vars->i++;
			while (context[vars->i] && context[vars->i] != SINGLE_QUOTE)
				vars->new_string[vars->j++] = context[vars->i++];
		}
		else
			vars->new_string[vars->j++] = context[vars->i];
		vars->i++;
	}
	vars->new_string[vars->j] = '\0';
}

char	*remove_quotes(char *context)
{
	t_remove_quotes_vars	vars;

	if (!context)
		return (NULL);
	vars.new_string_length = get_new_string_length(context);
	vars.new_string = malloc(sizeof(char) * (vars.new_string_length + 1));
	vars.i = 0;
	vars.j = 0;
	remove_quotes_helper(context, &vars);
	return (vars.new_string);
}

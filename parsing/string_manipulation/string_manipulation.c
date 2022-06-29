/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string_manipulation.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-hiou <ael-hiou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/24 11:48:44 by ael-hiou          #+#    #+#             */
/*   Updated: 2022/06/29 09:09:07 by ael-hiou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "string_manipulation.h"

void	in_a_quote(int *in_quote, int SINGLE_OR_DOUBLE)
{
	if (*in_quote == SINGLE_OR_DOUBLE)
		*in_quote = 0;
	else if (*in_quote == 0)
		*in_quote = SINGLE_OR_DOUBLE;
}

int	get_new_string_length(char *context)
{
	int	inside_quotes_counter;
	int	i;

	i = 0;
	inside_quotes_counter = 0;
	while (context[i])
	{
		if (context[i] == DOUBLE_QUOTE)
			quotes_counter(context, &i, DOUBLE_QUOTE, &inside_quotes_counter);
		else if (context[i] == SINGLE_QUOTE)
			quotes_counter(context, &i, SINGLE_QUOTE, &inside_quotes_counter);
		else
			inside_quotes_counter++;
		i++;
	}
	return (inside_quotes_counter);
}

void	add_space_helper(char *context, t_add_space_vars *vars)
{
	if ((context[vars->i] == RED_INPUT || context[vars->i] == RED_OUTPUT \
	|| context[vars->i] == PIPE))
	{
		vars->new_string[vars->j++] = context[vars->i];
		if (vars->in_quote == 0)
			vars->new_string[vars->j++] = SPACE;
	}
	else if ((context[vars->i + 1] == RED_INPUT || context[vars->i + 1] \
	== RED_OUTPUT || context[vars->i + 1] == PIPE))
	{
		vars->new_string[vars->j++] = context[vars->i];
		if (vars->in_quote == 0)
			vars->new_string[vars->j++] = SPACE;
	}
	else
		vars->new_string[vars->j++] = context[vars->i];
}

char	*add_space(char *context, int redirections_counter)
{
	t_add_space_vars	vars;

	vars.new_string_length = ft_strlen(context) + redirections_counter + 1;
	vars.new_string = malloc(sizeof(char) * (vars.new_string_length));
	vars.i = -1;
	vars.j = 0;
	vars.in_quote = 0;
	while (context[++(vars.i)])
	{
		if (context[vars.i] == DOUBLE_QUOTE)
			in_a_quote(&vars.in_quote, DOUBLE_QUOTE);
		else if (context[vars.i] == SINGLE_QUOTE)
			in_a_quote(&vars.in_quote, SINGLE_QUOTE);
		add_space_helper(context, &vars);
	}
	vars.new_string[vars.j] = '\0';
	return (vars.new_string);
}

char	*get_new_context(t_data *entered_data)
{
	int		counter;
	int		in_quote;
	char	*s;

	entered_data->index = 0;
	counter = 0;
	in_quote = 0;
	while (entered_data->context[entered_data->index])
	{
		if (entered_data->context[entered_data->index] == SINGLE_QUOTE)
			replacing_space(entered_data, SINGLE_QUOTE);
		else if (entered_data->context[entered_data->index] == DOUBLE_QUOTE)
			replacing_space(entered_data, DOUBLE_QUOTE);
		else if ((entered_data->context[entered_data->index] == \
		RED_INPUT || entered_data->context[entered_data->index] == \
		RED_OUTPUT || entered_data->context[entered_data->index] == PIPE))
			counter += 2;
		entered_data->index++;
	}
	s = add_space(entered_data->context, counter);
	free (entered_data->context);
	return (s);
}

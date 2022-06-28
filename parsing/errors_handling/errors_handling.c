/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors_handling.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ijmari <ijmari@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/24 10:51:35 by ael-hiou          #+#    #+#             */
/*   Updated: 2022/06/28 14:49:32 by ijmari           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "errors_handling.h"

void	skip_spaces(t_error_handling_vars *vars, char *context)
{
	while (context[vars->i] == SPACE)
			vars->i++;
}

int	check_unclosed_quotes(char *context)
{
	int	in_quote;
	int	i;

	in_quote = 0;
	i = 0;
	while (context[i])
	{
		if (context[i] == DOUBLE_QUOTE)
			in_a_quote(&in_quote, DOUBLE_QUOTE);
		else if (context[i] == SINGLE_QUOTE)
			in_a_quote(&in_quote, SINGLE_QUOTE);
		i++;
	}
	return (in_quote);
}

int	error_handling_helper(t_error_handling_vars *vars, char *context)
{
	if (context[vars->i] == RED_INPUT && vars->in_quote == 0)
	{
		vars->i++;
		skip_spaces(vars, context);
		if (context[vars->i] == RED_OUTPUT || context[vars->i] == '\0'
			|| context[vars->i] == PIPE)
			return (TRUE);
		if (context[vars->i] == RED_INPUT)
		{
			if (context[++vars->i] == '\0' || context[vars->i] == \
					RED_INPUT || context[vars->i] == RED_OUTPUT)
				return (TRUE);
		}
	}
	else if (context[vars->i] == RED_OUTPUT && vars->in_quote == 0)
	{
		vars->i++;
		skip_spaces(vars, context);
		if (context[vars->i] == RED_INPUT || context[vars->i] == '\0'
			|| context[vars->i] == PIPE)
			return (TRUE);
		if (context[vars->i] == RED_OUTPUT)
		{
			skip_spaces(vars, context);
			if (context[vars->i] == '\0' || context[vars->i] == \
					RED_OUTPUT || context[vars->i] == RED_INPUT)
				return (TRUE);
		}
	}
	return (FALSE);
}

int	error_handling(char *context)
{
	t_error_handling_vars	vars;

	vars.i = 0;
	vars.in_quote = 0;
	vars.is_first_enter = 0;
	if (check_unclosed_quotes(context))
		return (TRUE);
	while (context[vars.i])
	{
		if (context[vars.i] == DOUBLE_QUOTE)
			in_a_quote(&vars.in_quote, DOUBLE_QUOTE);
		else if (context[vars.i] == SINGLE_QUOTE)
			in_a_quote(&vars.in_quote, SINGLE_QUOTE);
		skip_spaces(&vars, context);
		if (context[vars.i] == PIPE && vars.in_quote == 0
			&& vars.is_first_enter == 0)
			return (TRUE);
		vars.is_first_enter = 1;
		if (context[vars.i] == PIPE && vars.in_quote == 0)
		{
			vars.i++;
			skip_spaces(&vars, context);
			if (context[vars.i] == PIPE || context[vars.i] == '\0'
				|| context[vars.i] == RED_INPUT
				|| context[vars.i] == RED_OUTPUT)
				return (TRUE);
		}
		else if (error_handling_helper(&vars, context))
			return (TRUE);
		if (context[vars.i] == '\0')
			return (FALSE);
		vars.i++;
	}
	return (FALSE);
}

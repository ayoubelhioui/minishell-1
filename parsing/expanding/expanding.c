/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expanding.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-hiou <ael-hiou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/24 10:03:23 by ael-hiou          #+#    #+#             */
/*   Updated: 2022/06/25 17:05:59 by ael-hiou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expanding.h"

void	expanding_helper(t_expanding *vars)
{
	if ((vars->data.context[vars->data.index] == RED_INPUT)
		&& (vars->data.context[vars->data.index + 1] == RED_INPUT))
		vars->is_limiter = TRUE;
	else if (vars->data.context[vars->data.index] == SPACE)
		vars->is_limiter = FALSE;
	else if (vars->data.context[vars->data.index] == DOUBLE_QUOTE)
		in_a_quote(&vars->in_quote, DOUBLE_QUOTE);
	else if (vars->data.context[vars->data.index] == SINGLE_QUOTE)
		in_a_quote(&vars->in_quote, SINGLE_QUOTE);
}

void	expanding_init(t_expanding *vars, char *str)
{
	vars->in_quote = 0;
	vars->is_limiter = FALSE;
	vars->saver = NULL;
	vars->data.context = str;
	vars->data.index = -1;
	vars->j = 0;
	vars->x = 0;
}

void	expanding_final_part(t_expanding *vars)
{
	char	*temp;

	if (vars->x < vars->data.index)
	{
		temp = vars->saver;
		vars->saver = expanding_join(vars->saver, vars->temp);
		free(temp);
	}
	free(vars->temp);
}

char	*dollar_sign_found(t_data *data, char **env, \
char *saver, int *last_dollar_index)
{
	t_dollar_sign_vars	vars;

	vars.env_value = NULL;
	vars.index_saver = data->index;
	while ((data->context[data->index]) \
	&& ((ft_isalnum(data->context[data->index])) \
	|| (data->context[data->index] == UNDER_SCORE)))
		data->index++;
	vars.first_part = ft_substr(data->context, *last_dollar_index, \
	vars.index_saver - *last_dollar_index - 1);
	*last_dollar_index = data->index;
	vars.to_be_expanded = ft_substr(data->context, vars.index_saver, \
	data->index - vars.index_saver);
	vars.temp = ft_substr(data->context, vars.index_saver + 1, \
	data->index - vars.index_saver - 1);
	vars.temp1 = ft_strdup("minishell");
	get_value(&vars, env);
	all_about_free(vars.temp1, vars.temp, vars.to_be_expanded);
	vars.temp = expanding_join(vars.first_part, vars.env_value);
	vars.temp1 = saver;
	saver = expanding_join(saver, vars.temp);
	if (vars.temp1)
		free(vars.temp1);
	all_about_free(vars.temp, vars.env_value, vars.first_part);
	return (saver);
}

char	*expanding(char *str, char **env)
{
	t_expanding	vars;

	expanding_init(&vars, str);
	while (vars.data.context[++vars.data.index])
	{
		expanding_helper(&vars);
		if ((vars.data.context[vars.data.index] == DOLLAR_SIGN) && \
		(vars.in_quote != SINGLE_QUOTE) && (vars.is_limiter == FALSE) && \
		(ft_isalnum(vars.data.context[vars.data.index + 1]) || \
		vars.data.context[vars.data.index + 1] == UNDER_SCORE))
		{
			vars.data.index++;
			vars.saver = dollar_sign_found(&vars.data, \
			env, vars.saver, &vars.j);
			vars.data.index--;
			vars.x = vars.data.index + 1;
		}
		if (!vars.data.context[vars.data.index])
			break ;
	}
	vars.temp = ft_substr(vars.data.context, vars.x, \
	ft_strlen(vars.data.context) - vars.x);
	expanding_final_part(&vars);
	free (str);
	return (vars.saver);
}

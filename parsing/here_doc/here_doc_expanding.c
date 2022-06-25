/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc_expanding.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ijmari <ijmari@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/25 15:41:53 by ael-hiou          #+#    #+#             */
/*   Updated: 2022/06/25 16:36:32 by ijmari           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "here_doc.h"

char	*expanding_here_doc(char *str, char **env)
{
	t_expanding	vars;

	expanding_init(&vars, str);
	while (vars.data.context[++vars.data.index])
	{
		expanding_helper(&vars);
		if ((vars.data.context[vars.data.index] == DOLLAR_SIGN) && \
		(vars.is_limiter == FALSE) && \
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

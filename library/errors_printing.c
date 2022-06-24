/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors_printing.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-hiou <ael-hiou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/24 16:10:35 by ijmari            #+#    #+#             */
/*   Updated: 2022/06/24 16:18:01 by ael-hiou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	export_error(char **split_arg, char **arg, int *i)
{
	printf("export: \'%s\': not a valid identifier\n", arg[(*i)++]);
	if (split_arg)
		ft_free(split_arg);
	g_key.exit_stat = 1;
}

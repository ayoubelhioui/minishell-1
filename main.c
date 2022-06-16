/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-hiou <ael-hiou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/15 10:32:20 by ael-hiou          #+#    #+#             */
/*   Updated: 2022/06/16 12:50:02 by ael-hiou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void    fuck(t_expanding *vars)
{
    vars->in_quote++;
}
int main()
{
    t_expanding vars;
    vars.in_quote = 0;
    fuck(&vars);
    printf("It Is : %d\n", vars.in_quote);
}
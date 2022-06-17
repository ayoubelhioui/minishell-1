/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-hiou <ael-hiou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/15 10:32:20 by ael-hiou          #+#    #+#             */
/*   Updated: 2022/06/17 14:37:33 by ael-hiou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void    fuck(t_remove_quotes_vars *var)
{
    var->new_string[0] = 'a';
    var->new_string[1] = 'a';
    var->new_string[2] = 'a';
    var->new_string[3] = '\0';
    // printf("It Is : %s\n", var->new_string);

}
int main()
{
    t_remove_quotes_vars var;

    var.new_string = malloc(sizeof(char) * 4);
    fuck(&var);
    printf("It Is : %s\n", var.new_string);
}
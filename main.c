/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-hiou <ael-hiou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/13 16:30:41 by ael-hiou          #+#    #+#             */
/*   Updated: 2022/05/17 17:33:08 by ael-hiou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int test(char *context)
{
    int in_a_quote = 0;
    int counter = 0;
    int i = 0;

    while (context[i])
    {
        if (context[i] == DOUBLE_QUOTE)
        {
            if (in_a_quote == DOUBLE_QUOTE)
                in_a_quote = 0;
            else if (in_a_quote == 0)
                in_a_quote = DOUBLE_QUOTE;
        }
        else if (context[i] == SINGLE_QUOTE)
        {
            if (in_a_quote == SINGLE_QUOTE)
                in_a_quote = 0;
            else if (in_a_quote == 0)
                in_a_quote = SINGLE_QUOTE;
        }
        if ((context[i] == DOLLAR_SIGN) && (in_a_quote == 0))
            counter++;
        i++;
    }
}

int main(int ac, char **av, char **env)
{
    printf("It Is : %d\n", test())
}
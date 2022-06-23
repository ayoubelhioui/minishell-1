/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-hiou <ael-hiou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/23 11:10:04 by ael-hiou          #+#    #+#             */
/*   Updated: 2022/06/23 14:17:49 by ael-hiou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
void    test_it()
{
      char **s;

    s = malloc(sizeof(char *));
    s[0] = NULL;
    // free(s[0]);
    free (s);
}
int main()
{
    test_it();

    system("leaks a.out");
}
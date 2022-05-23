/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-hiou <ael-hiou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/23 11:59:58 by ael-hiou          #+#    #+#             */
/*   Updated: 2022/05/23 14:23:12 by ael-hiou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int main(int ac, char **av, char **env)
{
    char *path = "/bin/ls";
    char *s[] = {"ls", "-la", NULL};
    execve(path, s, env);
    printf("Hello World\n");
}
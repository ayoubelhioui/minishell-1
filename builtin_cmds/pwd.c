/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ijmari <ijmari@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/14 14:51:25 by ijmari            #+#    #+#             */
/*   Updated: 2022/06/14 14:52:01 by ijmari           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	pwd(void)
{
	char	*cwd;

	cwd = getcwd(NULL, sizeof(cwd));
	if (!cwd)
		perror("pwd error");
	else
		printf("%s\n", cwd);
	free(cwd);
}

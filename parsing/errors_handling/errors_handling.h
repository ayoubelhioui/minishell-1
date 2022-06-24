/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handling.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-hiou <ael-hiou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/24 10:51:48 by ael-hiou          #+#    #+#             */
/*   Updated: 2022/06/24 11:00:21 by ael-hiou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# ifndef ERROR_HANDLING_H
# define ERROR_HANDLING_H
#include "../../minishell.h"

int check_unclosed_quotes(char *context);
int error_handling_helper(t_error_handling_vars *vars, char *context);
int error_handling(char *context);

# endif
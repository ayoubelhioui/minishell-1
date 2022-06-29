/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors_handling.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-hiou <ael-hiou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/24 16:38:51 by ael-hiou          #+#    #+#             */
/*   Updated: 2022/06/28 18:51:15 by ael-hiou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ERRORS_HANDLING_H
# define ERRORS_HANDLING_H
# include "../../minishell.h"

int	check_unclosed_quotes(char *context);
int	redirections_handling(t_error_handling_vars *vars, char *context);
int	error_handling(char *context);
int	pipe_error_handling(t_error_handling_vars *vars, char *context);
#endif

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_argument.h                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-hiou <ael-hiou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/24 11:31:10 by ael-hiou          #+#    #+#             */
/*   Updated: 2022/06/24 14:03:44 by ael-hiou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COMMAND_ARGUMENT_H
# define COMMAND_ARGUMENT_H
# include "../../minishell.h"

int		get_cmd_args(char **data, t_returned_data *returned_data, char **env);
void	args_final_touch(t_returned_data *returned_data, char **env);
void	get_cmd_args_helper1(char **data, int *i, int *j, \
		t_returned_data *returned_data);
void	get_cmd_args_helper(char **data, t_returned_data \
		*returned_data, char **env);
int		get_args_length(char **data);
int		get_cmd_path_helper(t_cmd_path *vars);
char	*get_command_path(char **env_variables, char *command);
void	freeing(char **s);
void	back_space(char *context);
#endif

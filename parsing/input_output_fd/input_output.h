/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_output.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ijmari <ijmari@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/24 11:17:09 by ael-hiou          #+#    #+#             */
/*   Updated: 2022/06/25 14:29:19 by ijmari           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INPUT_OUTPUT_H
# define INPUT_OUTPUT_H

# include "../../minishell.h"
# include "../here_doc/here_doc.h"

void	pipe_handling_helper(int i, int commands_number, \
int (*pipes_array)[2], t_returned_data *temp);
void	pipe_handling(int commands_number, \
char **splitted_by_pipe, t_returned_data *temp);
void	getting_output_fd_helper(char **s, int i, \
t_returned_data *returned_data);
void	getting_output_fd(char *str, t_returned_data \
*returned_data, int unexisting_file_idx);
int		getting_input_fd(t_returned_data \
*returned_data, char **s);
void	getting_input_output_fd(char *str, t_returned_data *temp);

#endif

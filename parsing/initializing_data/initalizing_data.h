/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initalizing_data.h                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-hiou <ael-hiou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/24 11:58:29 by ael-hiou          #+#    #+#             */
/*   Updated: 2022/06/24 12:08:52 by ael-hiou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INITIALIZING_DATA_H
# define INITIALIZING_DATA_H
#include "../../minishell.h"
#include "../string_manipulation/string_manipulation.h"
#include "../expanding/expanding.h"
#include "../here_doc/here_doc.h"
#include "../input_output_fd/input_output.h"
#include "../command_argument/command_argument.h"
void    add_to_list(t_list  **head, char *string);
void	returned_data_addback(t_returned_data **returned_data, t_returned_data *new);
void    create_returned_nodes(t_returned_data **returned_data, int commands_number);
int     preparing(t_data *entered_data, t_list *env, t_returned_data **returned_data);

#endif

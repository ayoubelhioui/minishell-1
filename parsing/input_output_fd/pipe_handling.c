/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_handling.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-hiou <ael-hiou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/24 11:18:32 by ael-hiou          #+#    #+#             */
/*   Updated: 2022/06/24 11:18:53 by ael-hiou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "input_output.h"

void    pipe_handling_helper(int i, int commands_number, int (*pipes_array)[2], t_returned_data *temp)
{
    if (commands_number > 1)
    {
        if (i < commands_number - 1)
            pipe(pipes_array[i]);
        if (i == 0)
            temp->output_fd = pipes_array[i][STD_OUTPUT];
        else if (i == commands_number - 1)
            temp->input_fd = pipes_array[i - 1][STD_INPUT];
        else
        {
            temp->input_fd = pipes_array[i - 1][STD_INPUT];
            temp->output_fd = pipes_array[i][STD_OUTPUT];
        } 
    }
}
    
void    pipe_handling(int commands_number, char **splitted_by_pipe, t_returned_data *temp)
{
    int (*pipes_array)[2];
    int i;
    int temp_input;
	char	**ptr;

    i = -1;
    pipes_array = malloc(sizeof(int *) * (commands_number - 1));
    while (splitted_by_pipe[++i])
    {
        temp_input = temp->input_fd;
        pipe_handling_helper(i, commands_number, pipes_array, temp);
        getting_input_output_fd(splitted_by_pipe[i], temp);
		ptr = ft_split(splitted_by_pipe[i], SPACE);
        if (find_heredoc_position(ptr))
            temp->input_fd = temp_input;
        temp = temp->next;
		ft_free(ptr);
    }
    free (pipes_array);
}

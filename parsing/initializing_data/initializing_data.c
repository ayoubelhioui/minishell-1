/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initializing_data.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ijmari <ijmari@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/24 11:59:02 by ael-hiou          #+#    #+#             */
/*   Updated: 2022/06/25 15:12:03 by ijmari           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "initializing_data.h"

void	add_to_list(t_list **head, char *string)
{
	t_list	*new;

	new = ft_lstnew(string);
	ft_lstadd_back(head, new);
}

void	returned_data_addback(t_returned_data \
**returned_data, t_returned_data *new)
{
	t_returned_data	*temp;

	temp = (*returned_data);
	if (*returned_data)
	{
		while (temp->next)
			temp = temp->next;
		temp->next = new;
	}
	else
		*returned_data = new;
}

void	create_returned_nodes(t_returned_data \
**returned_data, int commands_number)
{
	t_returned_data	*new;

	while (commands_number > 0)
	{
		new = malloc(sizeof(t_returned_data));
		new->cmd_dup = NULL;
		new->cmd_path = NULL;
		new->next = NULL;
		new->args = malloc(sizeof(char *));
		new->args[0] = NULL;
		new->str_idx = 0;
		new->flag = 0;
		new->is_executable = TRUE;
		new->input_fd = STD_INPUT;
		new->output_fd = STD_OUTPUT;
		returned_data_addback(returned_data, new);
		commands_number--;
	}
}

int	preparing(t_data *entered_data, \
t_list *env, t_returned_data **returned_data)
{
	t_preparing_vars	vars;

	vars.new_env = get_new_env(env);
	entered_data->context = expanding(entered_data->context, vars.new_env);
	entered_data->context = get_new_context(entered_data);
	vars.splitted_by_pipe = ft_split(entered_data->context, PIPE);
	vars.commands_number = get_length(vars.splitted_by_pipe);
	vars.splitted_by_space = ft_split(entered_data->context, SPACE);
	free(entered_data->context);
	create_returned_nodes(returned_data, vars.commands_number);
	vars.ret = heredoc_searcher(vars.splitted_by_space, \
	*returned_data, vars.new_env);
	if (vars.ret == -4 && g_key.flag == 6)
	{
		free_splits(vars.splitted_by_pipe, vars.splitted_by_space);
		free (vars.new_env);
		return (-4);
	}
	pipe_handling(vars.commands_number, vars.splitted_by_pipe, *returned_data);
	get_cmd_args(vars.splitted_by_pipe, *returned_data, vars.new_env);
	args_final_touch(*returned_data);
	free_splits(vars.splitted_by_pipe, vars.splitted_by_space);
	free(vars.new_env);
	return (1);
}

#include "../minishell.h"

void	close_all_pipes(t_returned_data *head)
{
	int	i;

	i = 0;
	while (head)
	{
		if (head->input_fd != STD_INPUT)
			close(head->input_fd);
		if (head->output_fd != STD_OUTPUT)
			close(head->output_fd);
		head = head->next;
		i++;
	}
}
void	close_unused_pipes(t_returned_data *head, t_returned_data *curr, char **env, int id)
{
	static int k;
	int	h;
	h = 0;
	while (head)
	{
		if (head != curr)
		{
			if (head->input_fd != STD_INPUT)
				close(head->input_fd);
			if (head->output_fd != STD_OUTPUT)
				close(head->output_fd);
		}
		head = head->next;
		h++;
	}
	k++;
}

void 	fill_list(t_returned_data *data, char **env, t_list **env_l)
{
	int	*id;
	int	counter;
	char *path;
	t_returned_data *t = data;
	t_returned_data *temp = data;
	int	check;
	int	len;
	counter = 0;
	while (temp)
	{
		counter++;
		temp = temp->next;
	}
	len = counter;
	id = malloc(counter * sizeof(int));
	counter = 0;
	if (len == 1 && built_exist(data, env_l) && data->is_executable)
		built_check(data, env_l);
	else
	{
		while (data)
		{
			if (data->is_executable)
			{
				id[counter] = fork();
				if (id[counter] == 0)
				{		
					close_unused_pipes(t, data, env, id[counter]);
			{
			check = built_exist(data, env_l);
			if (data->input_fd != 0 && !check)
			{
				dup2(data->input_fd, STD_INPUT);
				close (data->input_fd);
			}
			if (check)
				if (data->input_fd)
					close (data->input_fd);
			if (data->output_fd != 1)
			{
				dup2(data->output_fd, STD_OUTPUT);
				close (data->output_fd);
			}
			if (built_check(data, env_l))
				exit(1);
			else if (execve(get_command_path(env, data->cmd_path), data->args, env) == -1)
			{
				printf("command not found\n");
				exit(1);
			}
		}
	}
	}
		counter++;
		data = data->next;
	}
	}
	close_all_pipes(t);
	counter = 0;
	while (counter < len)
		waitpid(id[counter++], &g_exit_stat, 0);
}

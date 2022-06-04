#include "../minishell.h"

void	close_all_pipes(t_returned_data *head)
{
	while (head)
	{
		if (head->input_fd != STD_INPUT)
		{
			printf("WAS HERE\n");
			close(head->input_fd);
		}
		if (head->output_fd != STD_OUTPUT)
		{
			printf("WAS HERE\n");	
			close(head->output_fd);
		}
		head = head->next;
	}
}
void	close_unused_pipes(t_returned_data *head, t_returned_data *curr, char **env)
{
	int	i;

	i = 0;
	static int j;
	while (head)
	{
		if (head != curr)
		{
			if (head->input_fd != STD_INPUT)
			{
				printf("WAS HERE in %d\n", j);
				close(head->input_fd);
			}
			if (head->output_fd != STD_OUTPUT)
			{
				printf("WAS HERE in %d\n", j);
				close(head->output_fd);
			}
		}
		head = head->next;
	}
	j++;
}

void	fill_list(t_returned_data *data, char **env)
{
	int	*id;
	int	counter;
	char *path;
	t_returned_data *t = data;
	t_returned_data *temp = data;
	int	len;
	// int j = 0;
	// while (temp)
	// {
	// 	printf("COMMAND IS : %s\n", temp->cmd_path);
	// 	j = 0;
	// 	while (temp->args[j])
	// 		printf("ARGS IS : %s\n", temp->args[j++]);
	// 	temp = temp->next;
	// }
	counter = 0;
	while (temp)
	{
		counter++;
		temp = temp->next;
	}
	len = counter;
	id = malloc(counter * sizeof(int));
	counter = 0;
	while (data)
	{
		id[counter] = fork();
		if (id[counter] == 0)
		{	
			if (data->is_executable)
			{
				close_unused_pipes(t, data, env);
				// if (data->input_fd != STD_INPUT)
				// {
					dup2(data->input_fd, STD_INPUT);
					close (data->input_fd);
				// }
				// if (data->output_fd != STD_OUTPUT)
				// {
					dup2(data->output_fd, STD_OUTPUT);
					close (data->output_fd);
				// }
				path = get_command_path(env, data->cmd_path);
				// dprintf(2, "CMD is %s, ARGS ARE %s %s %s\n", path, data->args[0], data->args[1], data->args[2]);
				if (execve(path, data->args, NULL) == -1)
					dprintf(2, "HEY \n");
			}	
		}
			// else
			// {
			// 		dprintf(2, "hi %i\n",counter);
			//         waitpid(id[counter], NULL, 0);
			// }
		data = data->next;
		counter++;
	}
	close_all_pipes(t);
	counter = 0;
	while(counter < len)
	{
		printf("OO\n");
		waitpid(id[counter], NULL, 0);
		counter++;
	}
}
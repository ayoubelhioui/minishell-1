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

void	close_unused_pipes(t_returned_data *head, t_returned_data *curr)
{
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
	}
}

void	handle_the_cmd(t_returned_data *t, t_returned_data *data, \
	t_list **env_l, char **env)
{
	int	check;

	signal(SIGQUIT, sig_quit);
	close_unused_pipes(t, data);
	check = built_exist(data->cmd_dup);
	if (data->cmd_path == NULL && !check)
	{
		printf("%s: No such file or directory\n", data->cmd_dup);
		g_key.exit_stat = 127;
		ft_exit("127");
	}
	if (data->input_fd != 0 && !check)
		dup_and_close(data, 'i');
	if (check)
	{
		if (data->input_fd)
			close (data->input_fd);
	}
	if (data->output_fd != 1)
		dup_and_close(data, 'o');
	if (built_check(data, env_l))
		ft_exit("0");
	else if (execve(data->cmd_path, \
	data->args, env) == -1)
	{
		printf("command not found\n");
		g_key.exit_stat = 127;
		ft_exit("127");
	}
}

void	check_and_exec(t_returned_data *data, t_list **env_l, \
	char **env)
{
	int				i;
	t_returned_data	*t;
	int				id;

	t = data;
	i = 0;
	while (data)
	{
		if (data->is_executable)
		{
			id = fork();
			if (id == 0)
			{
				handle_the_cmd(t, data, env_l, env);
			}
		}
		i++;
		data = data->next;
	}
}

void	fill_list(t_returned_data *data, char **env, t_list **env_l)
{
	int				*id;
	int				counter;
	t_returned_data	*t;
	int				saver;

	counter = lst_count(data);
	if (counter == 1 && built_exist(data->cmd_dup) && data->is_executable)
	{
		saver = dup(1);
		if (data->output_fd != 1)
			dup2(data->output_fd, 1);
		built_check(data, env_l);
		dup2(saver, 1);
	}
	else
	{
		g_key.flag_for_here = 2;
		check_and_exec(data, env_l, env);
	}
	close_and_wait(data, counter);
	g_key.flag_for_here = 0;
}

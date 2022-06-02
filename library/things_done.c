#include "../minishell.h"

void	fill_list(t_returned_data *env)
{
	int	*id;
	int	i;

	id = malloc(ft_lstsize((t_list *) env) * sizeof(int));
	i = 0;
	while (env)
	{
		id[i] = fork();
		if (id[i] == 0)
		{
			if (env->is_executable)
			{
				dup2(0, env->input_fd);
				close(env->input_fd);
				dup2(1, env->output_fd);
				close(env->output_fd);
				execve(env->cmd_path, env->args, NULL);
			}
		}
		close(env->input_fd);
		close(env->output_fd);
		env = env->next;
		i++;
	}
	i = 0;
	while (id[i])
		waitpid(id[i++], NULL, 0);
}
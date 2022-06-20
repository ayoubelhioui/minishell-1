#include "../minishell.h"

int	built_exist(char *cmd_path)
{
	if (!ft_strcmp(cmd_path, "cd"))
		return (1);
	else if (!ft_strcmp(cmd_path, "pwd"))
		return (1);
	else if (!ft_strcmp(cmd_path, "env"))
		return (1);
	else if (!ft_strcmp(cmd_path, "echo"))
		return (1);
	else if (!ft_strcmp(cmd_path, "exit"))
		return (1);
	else if (!ft_strcmp(cmd_path, "export"))
		return (1);
	else if (!ft_strcmp(cmd_path, "unset"))
		return (1);
	return (0);
}

int	built_check(t_returned_data *ret, t_list **env)
{
	if (!ft_strcmp(ret->cmd_dup, "cd"))
		cd(&ret->args[1], env);
	else if (!ft_strcmp(ret->cmd_dup, "pwd"))
		pwd();
	else if (!ft_strcmp(ret->cmd_dup, "env"))
		ft_env(env);
	else if (!ft_strcmp(ret->cmd_dup, "echo"))
		ft_echo(&ret->args[1]);
	else if (!ft_strcmp(ret->cmd_dup, "exit"))
	{
		printf("exit\n");
		if (ret->args[1])
		{
			ft_exit(&ret->args[1]);
		}
		else
			exit(0);
	}
	else if (!ft_strcmp(ret->cmd_dup, "export"))
		ft_export(env, &ret->args[1]);
	else if (!ft_strcmp(ret->cmd_dup, "unset"))
		ft_unset(env, &ret->args[1]);
	else
		return (0);
	return (1);
}

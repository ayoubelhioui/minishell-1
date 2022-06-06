#include "../minishell.h"

int	built_check(t_returned_data *ret, t_list **env)
{
	if (!ft_strcmp(ret->cmd_path, "/usr/bin/cd"))
		cd(&ret->args[1], env);
	else if (!ft_strcmp(ret->cmd_path, "/bin/pwd"))
		pwd();
	else if (!ft_strcmp(ret->cmd_path, "/usr/bin/env"))
		ft_env(env);
	else if (!ft_strcmp(ret->cmd_path, "/bin/echo"))
	{
		ft_echo((const char **) &ret->args[1]);
	}
	else if (!ft_strcmp(ret->cmd_path, "exit"))
		ft_exit();
	else if (!ft_strcmp(ret->cmd_path, "export"))
	{
		ft_export(env, &ret->args[1]);
	}
	else if (!ft_strcmp(ret->cmd_path, "unset"))
		ft_unset(env, &ret->args[1]);
	else
		return (0);
	return (1);
}
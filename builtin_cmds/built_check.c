#include "../minishell.h"

void	built_check(char *context, t_list **env)
{
	char	**full_info;
	char	*command;
	char	**args;
	int		i;

	full_info = ft_split(context, ' ');
	command = full_info[0];
	i = 1;
	while (full_info[i] && strcmp(full_info[i], "|"))
		i++;
	args = malloc(i * sizeof(char *)); 
	i = 1;
	while (full_info[i] && strcmp(full_info[i], "|"))
	{
		args[i - 1] = full_info[i];
		i++;
	}
	args[i - 1] = NULL;
	if (!strcmp(command, "cd"))
		cd(args, env);
	else if (!strcmp(command, "pwd"))
		pwd();
	else if (!strcmp(command, "env"))
		ft_env(env);
	else if (!strcmp(command, "echo"))
		ft_echo((const char **) args);
	else if (!strcmp(command, "exit"))
		ft_exit();
	else if (!strcmp(command, "export"))
		ft_export(env, args);
	else if (!strcmp(command, "unset"))
		ft_unset(env, args);
	free(args);
	// ft_free(full_info);
}
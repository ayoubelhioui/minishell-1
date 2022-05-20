#include "../minishell.h"

void	cd(char **paths, t_list **env)
{
	int		ret;
	char	**buff;
	t_list	*curr;

	curr = *env;
	if (*paths == NULL || !ft_strcmp(paths[0], "~"))
	{
		while (curr)
		{
			if (ft_strstr(curr->content, "HOME"))
			{
				buff = ft_split(curr->content, '=');
				ret = chdir((const char *) buff[1]);
				ft_free(buff);
				break;
			}
			curr = curr->next;
		}
	}
	else
		ret = chdir((const char *) paths[0]);
	if (ret != 0)
		printf("cd: no such file or directory : %s\n", paths[0]);
	ft_free(paths);
}
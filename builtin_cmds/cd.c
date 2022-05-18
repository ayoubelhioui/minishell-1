#include "../minishell.h"

void	cd(char **paths)
{
	int	ret;

	int i = 0;
	ret = chdir((const char *) paths[0]);
	if (ret != 0)
		printf("cd: no such file or directory : %s\n", paths[0]);
}
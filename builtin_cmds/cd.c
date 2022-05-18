#include "../minishell.h"

void	cd(char **path)
{
	int	ret;

	printf("%s\n")
	if (!path)
		return ;
	ret = chdir((const char *) path[0]);
	if (ret != 0)
		printf("cd: no such file or directory : %s\n", *path);
}
#include "../minishell.h"

void	cd(const char *path)
{
	int	ret;

	if (!path)
		return ;
	ret = chdir(path);
	if (ret != 0)
		printf("cd: no such file or directory : %s\n", path);
}
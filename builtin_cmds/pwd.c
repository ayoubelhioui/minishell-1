#include "../minishell.h"

void	pwd(void)
{
	char *cwd;

	cwd = getcwd(NULL, sizeof(cwd));
	key.path = cwd;
    if (!cwd)
      perror("pwd error");
    else
      printf("%s\n", cwd);
	free(cwd);
}
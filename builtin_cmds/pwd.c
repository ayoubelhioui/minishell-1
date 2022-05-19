#include "../minishell.h"

void	pwd(void)
{
	char *cwd;

	cwd = getcwd(NULL, sizeof(cwd));
    if (!cwd)
      perror("pwd error");
    else
      printf("%s\n", cwd);
}
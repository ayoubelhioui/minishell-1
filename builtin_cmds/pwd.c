#include "../minishell.h"

void	pwd(void)
{
	char *cwd;

	cwd = malloc (sizeof(char) * 256);
    if (getcwd(cwd, sizeof(cwd)) == NULL)
      perror("pwd error");
    else
      printf("%s\n", cwd);
	free(cwd);
}
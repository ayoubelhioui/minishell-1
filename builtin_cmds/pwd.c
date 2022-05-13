#include "../minishell.h"

void	pwd(void)
{
	char cwd[256];


    if (getcwd(cwd, sizeof(cwd)) == NULL)
      perror("pwd error");
    else
      printf("%s\n", cwd);
}
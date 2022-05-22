#include "minishell.h"
int main()
{
	int j = 0;
	char **f=ft_split("OKKKK", '=');
	while (f[j])
		printf("%s\n", f[j++]);
}

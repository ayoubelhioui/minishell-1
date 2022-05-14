#include "../minishell.h"

void	ft_echo(const char *s, char opt)
{
	if (opt == 'n')
		printf("%s", s);
	else
		printf("%s\n", s);
}
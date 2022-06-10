#include "../minishell.h"

void	ft_echo(const char **s)
{
	int		i;
	char	c;

	c = 'a';
	i = 0;
	if (!ft_strcmp("$?", s[1]))
		printf("%d\n", 99);
	if (*s == NULL)
		printf("\n");
	if (!ft_strcmp(s[0], "-n"))
	{
		c = 'n';
		i = 1;
	}
	else
		i = 0;
	while (s[i])
	{
		if (c != 'n' && !s[i + 1])
			printf("%s\n", s[i]);
		else if (c == 'n' && !s[i + 1])
			printf("%s", s[i]);
		else
			printf("%s ", s[i]);
		i++;
	}
}
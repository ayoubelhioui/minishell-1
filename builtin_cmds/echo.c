#include "../minishell.h"

void	print_string(char *s, char c, int flag)
{
	int	i;
	i = 0;
	while (s[i])
	{
		if (s[i] == '$' && s[i + 1] == '?')
		{
			if (flag == 1 && !s[i + 2] && c == 'a')
				printf("%d\n", key.exit_stat);
			else if (flag == 1 && !s[i + 2] && c == 'n')
				printf("%d", key.exit_stat);
			else
				printf("%d", key.exit_stat);
			i++;
		}
		else if (c == 'n' && flag && !s[i + 1])
			printf("%c", s[i]);
		else if (c != 'n' && flag && !s[i + 1])
			printf("%c\n", s[i]);
		else if (!flag && !s[i + 1])
			printf("%c ", s[i]);
		else
			printf("%c", s[i]);
		i++;
	}
}
void	ft_echo(char **s)
{
	int		i;
	char	c;
	c = 'a';

	i = 0;
	int j = 0;
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
		print_string(s[i], c, !s[i + 1]);
		i++;
	}
}
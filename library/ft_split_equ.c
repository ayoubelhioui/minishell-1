#include "../minishell.h"

int	len_e2(char *arg, int prev_len)
{
	int	len;
	int	i;	

	len = 0;
	if (arg[prev_len] == '\0')
		return (0);
	i = prev_len + 1;
	while (arg[i])
	{
		i++;
		len++;
	}
	return (len);
}
int	len_e1(char *arg)
{
	int	len;

	len = 0;
	while (arg[len] != '=' && arg[len])
		len++;
	return (len);
}

char	**fill_it(char *arg, char **s, int len, int len2)
{
	int	i;
	int	j;
	int	total;

	i = 0;
	j = 0;
	total = 0;
	s[0] = malloc((len + 1));
	while (j < len)
	{
		s[i][j] = arg[j];
		j++;
		total++;
	}
	s[i][j] = '\0';
	if (len2)
	{
		s[1] = malloc((len2 + 1));
		total = j + 1;
		i++;
		j = 0;
		while (j < len2)
		{
			s[i][j++] = arg[total++];
		}
		s[i][j] = '\0';
		s[2] = NULL;
	}
	else
		s[1] = NULL;
	return (s);
}

char	**split_with_equ(char *arg)
{
	int		len;
	int		len2;
	char	**s;

	len2 = 0;
	len	= len_e1(arg);
	len2 = len_e2(arg, len);
	s = malloc((len + len2 + 1) * sizeof(char *));
	return (fill_it(arg, s, len, len2));
}
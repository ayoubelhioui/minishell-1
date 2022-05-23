#include "../minishell.h"

int	len_2(char *arg, int len)
{
	int	len2;
	int	i;

	i = len + 2;
	len2 = 0;
	while (arg[i])
	{
		len2++;
		i++;
	}
	return (len2);
}
int	len_1(char *arg)
{
	int	len;

	len = 0;
	while (arg[len] != '+')
		len++;
	return (len);
}

char	**fill_the_d(int len1, int len2, char *arg, char **s)
{
	int	i;
	int	j;
	int	total;

	i = 0;
	j = 0;
	total = 0;
	s[0] = malloc((len1 + 1));
	while (j < len1)
	{
		s[i][j] = arg[j];
		j++;
		total++;
	}
	s[i][j] = '\0';
	s[1] = malloc((len2 + 1));
	total = j + 2;
	i++;
	j = 0;
	while (j < len2)
	{
		s[i][j] = arg[total];
		j++;
	}
	s[i][j] = '\0';
	s[2] = NULL;
	return (s);
}
char	**split_env(char *arg)
{
	char	**s;
	int		len1;
	int		len2;
	int		i;
	int		j;

	len1 = len_1(arg);
	len2 = len_2(arg, len1);
	s = malloc((len1 + len2 + 1) * sizeof(char *));
	s = fill_the_d(len1, len2, arg, s);
	return (s);
}
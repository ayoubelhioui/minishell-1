#include "../minishell.h"

int	ft_strstr(const char *s1, const char *s2)
{
	int	i;
	int	j;

	i = 0;
	if (s2[0] == '\0')
		return (0);
	while (s1[i])
	{
		j = 0;
		while (s1[i + j] == s2[j])
		{
			if (s2[j + 1] == '\0')
				return (1);
			j++;
		}
		i++;
	}
	return (0);
}
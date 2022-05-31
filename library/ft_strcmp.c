#include "../minishell.h"

int	ft_strcmp(const char *s1, const char *s2)
{
	size_t	i;

	i = 0;
	// printf("S1 Is : %s and S2 : %s\n", s1, s2);
	if (!s1 || !s2)
		return (1);
	while (s1[i] == s2[i] && s1[i] && s2[i])
		i++;
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}
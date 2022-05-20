#include "library.h"

int	ft_check(const char *set, char a)
{
	size_t	i;

	i = 0;
	while (set[i])
	{
		if (set[i] == a)
			return (1);
		i++;
	}
	return (0);
}

size_t	ft_right(const char *s1, const char *set)
{
	int	j;

	j = ft_strlen(s1) - 1;
	while (j >= 0)
	{
		if (!(ft_check(set, s1[j])))
			break ;
		j--;
	}
	return (j);
}

size_t	ft_left(const char *s1, const char *set)
{
	size_t	i;

	i = 0;
	while (s1[i])
	{
		if (!(ft_check(set, s1[i])))
			break ;
		i++;
	}
	return (i);
}

char	*ft_strtrim(char *s1, char *set)
{
	size_t	i;
	size_t	j;
	char	*str;
	size_t	k;

	if (!s1 || !set)
		return (NULL);
	k = 0;
	i = ft_left(s1, set);
	if (i == ft_strlen(s1))
		return (ft_strdup(""));
	j = ft_right(s1, set);
	str = malloc(sizeof(char) * j - i + 2);
	if (!str)
		return (NULL);
	while (i <= j)
		str[k++] = s1[i++];
	str[k] = '\0';
	return (str);
}

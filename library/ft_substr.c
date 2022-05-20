
#include "../minishell.h"

char	*copy(char const *s, char *str, unsigned int start, size_t len)
{
	size_t	i;

	i = 0;
	while (i < len)
	{
		str[i] = s[start];
		i++;
		start++;
	}
	str[i] = '\0';
	return (str);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t	i;
	size_t	total;
	char	*str;

	if (!s)
		return (NULL);
	i = 0;
	total = ft_strlen(s) - start;
	if (start >= ft_strlen(s))
		return (ft_strdup(""));
	if (start + len > ft_strlen(s))
	{
		str = malloc((total + 1) * sizeof(char));
		if (!str)
			return (NULL);
		return (copy(s, str, start, total));
	}
	else
	{
		str = malloc((len + 1) * sizeof(char));
		if (!str)
			return (NULL);
		return (copy(s, str, start, len));
	}
}
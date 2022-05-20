#include "library.h"

char	*ft_strdup(const char *src)
{
	size_t	n;
	size_t	i;
	char	*p;

	n = ft_strlen(src);
	p = malloc(sizeof(char) * (n + 1));
	if (p)
	{
		i = 0;
		while (src[i])
		{
			p[i] = src[i];
			i++;
		}
		p[i] = '\0';
	}
	else
		return (0);
	return (p);
}

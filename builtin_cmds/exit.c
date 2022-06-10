#include <stdlib.h>
#include <stdio.h>
extern int g_exit_stat;
void	ft_exit(int c)
{
	printf("%d\n", g_exit_stat);
	exit(g_exit_stat);
}
#include "minishell.h"

int		n_pipes(char **av)
{
	int	i;
	int	num;

	i = 0;
	num = 0;
	while (av[i])
	{
		if (strcmp(av[i], "|"))
			num++;
		i++;
	}
	return (num);
}
void	set(t_pipe_handling *p, char **av)
{
	int	num_pipes;

	num_pipes = n_pipes(av);
	p->pipes = malloc (sizeof(int *) * num_pipes);
	p->commands = malloc (sizeof(int) * )
}
int	main(int ac, char **av)
{
	t_pipe_handling	p;

	set(&p, av);
}
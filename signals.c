#include "minishell.h"

void sig_handler(int flag)
{
	if (flag == 0)
	{
		printf("\n");
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
	// int saver = dup(0);
}
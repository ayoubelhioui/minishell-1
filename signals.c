#include "minishell.h"

void sig_handler(int flag)
{
	if (!flag)
	{
		printf("\n");
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
	else
	{
		
	}
}
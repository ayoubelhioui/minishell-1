#include "minishell.h"

void sig_handler(int sig)
{
	int saver;
	if (key.flag_for_here == 0)
	{
		key.exit_stat = 1;
		printf("\n");
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
	else
	{
		key.saver = dup(0);
		close(0);
		dup2(key.saver, 0);
	}
}
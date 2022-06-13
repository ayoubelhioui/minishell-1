#include "minishell.h"

void sig_handler(int sig)
{
	int saver;
	if (key.flag_for_here == 0)
	{
		//printf("plll")
		key.exit_stat = 1;
		if (key.after_exit == 0)
			write(1, "\n", 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
	else
	{
		//printf("OK");
		key.flag = 6;
		key.saver = dup(0);
		close(0);
	}
}
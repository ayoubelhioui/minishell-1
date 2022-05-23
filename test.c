#include "minishell.h"
int main()
{
	char *s = strdup("OKKK");
	char *f;

	f = s;
	printf("%s\n", f);
	f = strdup("jjjjjj");
	printf("f :%s and s : %s\n", f, s);
}

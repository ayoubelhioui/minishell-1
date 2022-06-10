#include <stdio.h>
int l;

void lll()
{
	printf("ok %d\n", l);
}
int ccc()
{
	printf("%d\n", l);
	return l;
//	printf("%d\n", l);
}
int main()
{
	l = 5;
	int k = ccc();
	printf("k is %d\n", k);
	l = 9;
	lll();
}


#include <stdio.h>
/// & - operator => adresa lui a

/*
*/
void f(int a[]) 
{
	printf("%d", sizeof(a));
}

int array_decay()
{
	int a[100];
	int cate = 0;
	printf("%d\n", sizeof(a));
	f(a);

	return 0;
}

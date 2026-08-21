/*++
Se cere sa se citeasca de la tastatura un sir de numere, date in baza 10 ca numere cu semn 
(se citeste de la tastatura un sir de caractere si in memorie trebuie stocat un sir de numere).
--*/

#include <stdio.h>

int parse_intsAsm(char *s, int *v);

int main()
{
	char s[256];
	int v[100], n;

	printf("Introduceti numerele (separatate printr-un singur spatiu, nu se fac verificari aditionale)\n");
	fgets(s, sizeof(s), stdin);

	n = parse_intsAsm(s, v);

	printf("S-au citit %d numere\n", n);
	for (int i = 0; i < n; i++)
		printf("%d ", v[i]);

	return 0;
}
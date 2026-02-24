/*++
Se dau doua siruri continand caractere. 
Sa se calculeze si sa se afiseze rezultatul concatenarii tuturor caracterelor tip cifra zecimala 
din cel de-al doilea sir dupa cele din primul sir 
si invers, rezultatul concatenarii primului sir dupa al doilea.
--*/

#include <stdio.h>

void concatenareAsm(char* s1, char* s2, char* rez);

int main()
{
	char sir1[] = "abc123def";
	char sir2[] = "456ghi789";
	char rezultat[101];

	printf("Sirul 1 este: %s\n", sir1);
	printf("Sirul 2 este: %s\n", sir2);

	concatenareAsm(sir1, sir2, rezultat);
	printf("Rezultatul concatenarii este: %s", rezultat);
}
//Fie programul main.c in care se citeste de la tastatura un numar natural N, 
// un numar natural L (0 < L < 20) si N secvente de cel mult 20 de caractere.
// 
//Programul principal va apela pentru fiecare secventa de caractere citita procedura 
// VERIFICARE definita in fisierul modul1.asm care va afisa pe ecran mesajul "DA"
// daca secventa contine exact L caractere si cel putin unul din caracterele "!#@%&-+*)(", 
// si mesajul "NU" in caz contrar.
//Tot din programul principal va fi apelata pentru fiecare secventa de caractere procedura 
// ELIMINARE definita in modul2.asm care va afisa pe ecran secventa eliminand toate caracterele "!#@%&-+*)(".

//Exemplu:
//Se citeste de la tastatura N = 10, L = 3 si secventele :
//un! me-e d@i sapt# opt ban@ne %a* &mar ba+ (*) 

//Se va afisa :
//DA NU DA NU NU NU DA NU DA DA
//un mee di sapt opt banne a mar ba

#include <stdio.h>

void VERIFICARE(char sir[], int L);

void ELIMINARE(char sir[], char rez[]);

int main()
{
	int n,L,i;
	char siruri[101][21];


	printf("Introduceti n: ");
	scanf("%d", &n);
	printf("Introduceti L: ");
	scanf("%d", &L);

	for (i = 0; i < n; i++)
		scanf("%s", siruri[i]);

	//for (i = 0; i < n; i++)
		//printf("%s ", siruri[i]);

	for (i = 0; i < n; i++)
		VERIFICARE(siruri[i], L);

	printf("\n");

	for (i = 0; i < n; i++)
	{
		char eliminare[21];
		ELIMINARE(siruri[i], eliminare);
		printf(" ");
	}
		

	return 0;
}
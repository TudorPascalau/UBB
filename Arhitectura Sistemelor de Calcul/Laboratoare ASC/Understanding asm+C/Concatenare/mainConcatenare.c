
#include <stdio.h>

// functia declarata in modulConcatenare.asm
int asmConcat(char sir[], char sirR[]);

// functie folosita pentru a citit un sir de la tastatura
void citireSir(char sir[]);

void citireSirC(char sir[])
{
	scanf("%s", sir);
}

// sir global accesat din asmConcat
char str3[] = "0011223344";

int main()
{
	
	char str1[11];
	char strRez[31] = "";
	int lenStrRez = 0;

	printf("! se presupune ca sirule citie de la tastatura au lungimea 10! (nu se fac verificari suplimentare)\n");
	printf("Sirul 1 citit din modulul C:");
		citireSirC(str1);

	lenStrRez = asmConcat(str1, strRez);
	printf("\nSirul rezultat de lungime %d:\n%s", lenStrRez, strRez);

	return 0;

}
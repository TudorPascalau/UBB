
// Se da un numar a reprezentat pe 32 biti fara semn. Se cere sa se afiseze reprezentarea in baza 16 a lui a
// Precum si rezultatul permutarilor circulare ale cifrelor sale.

#include <stdio.h>

// variabila globala
unsigned int a;

void reprezentareHexaAsm(int);

int main()
{
	printf("a = ");
	scanf("%u", &a);

	printf("Reprezentarea lui %u in baza 16 este: ", a);
	reprezentareHexaAsm(a);

	int aux = a;
	int nr_cifre = 0;
	while (aux)
	{
		aux = aux / 10;
		nr_cifre = nr_cifre + 1;
	}

	int putere10 = 1;
	for (int i = 0; i < nr_cifre - 1; i++)
		putere10 = putere10 * 10;

	int c;

	printf("\nPermutarile circulare: \n");
	for (int i = 0; i < nr_cifre; i++)
	{
		c = a % 10;
		a = a / 10 + c * putere10;
		printf("%u\n", a);
	}


	return 0;
}
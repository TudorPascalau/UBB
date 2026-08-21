//Se citesc de la tastatura un numar natural n si n propozitii care contin cel putin n cuvinte 
// (nu se fac validari).
//Sa se afiseze sirul format prin concatenarea cuvintelor de pe pozitia i din propozitia i, i = 1, n
// (separate prin spatiu).

#include <stdio.h>
#include <string.h>

void concatenareASM(char*, char*);

int i, j;

int main()
{
	int n;
	scanf("%d\n", &n);

	char sir[256];
	char sir_rezultat[256] = "";

	for (i = 1; i <= n; i++)
	{
		fgets(sir, sizeof(sir), stdin);
		int len = 0;
		for (j=0; j<256; j++)
			if (sir[j] != '\0') len++;
			else break;

		int cuvant_start = 0;
		int numar_spatii = 0;
		for (j=0; j<len; j++)
			if (sir[j] == '_')
			{
				numar_spatii++;
				if (numar_spatii == i)
				{
					concatenareASM(sir + cuvant_start, sir_rezultat);
					break;
				}
					

				else cuvant_start = j + 1;
			}

		if (numar_spatii + 1 == i)
			concatenareASM(sir + cuvant_start, sir_rezultat);
		
	}


	printf("%s\n", sir_rezultat);

	return 0;
}
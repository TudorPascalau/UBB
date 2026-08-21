//Se citesc din fisierul numere.txt mai multe numere (pare si impare). 
// Sa se creeze 2 siruri rezultat N si P astfel: 
// N - doar numere impare si P - doar numere pare. 
// Afisati cele 2 siruri rezultate pe ecran.

#include <stdio.h>

int adaugaPareASM(int* src, int* dest, int n);

int i, j;
int main()
{
	FILE* file = fopen("numere.txt", "r");
	if (!file) {
		printf("Eroare la deschiderea fisierului.\n");
		return 1;
	}

	int v[100], n = 0;
	while (fscanf(file, "%d", &v[n]) == 1)
		n++;

	fclose(file);

	int pare[100];
	int nrP;
	nrP = adaugaPareASM(v, pare, n);

	FILE* out = fopen("rezultat.txt", "w");
	if (!out) {
		printf("Eroare la deschiderea fisierului rezultat.\n");
		return 1;
	}

	fprintf(out, "Numere pare:\n");
	for (int i = 0; i < nrP; i++)
		fprintf(out, "%d ", pare[i]);

	fprintf(out, "\n");

	return 0;
}
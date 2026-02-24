
#include <stdio.h>

//functia declarata in fisierul modulSuma.asm
int sumaNumere(int, int);

int main()
{
	int a, b, rezultat;
	printf("Introduceti doua numere intregi: ");
	scanf("%d %d", &a, &b);
	rezultat = sumaNumere(a, b);
	printf("Suma numerelor %d si %d este: %d\n", a, b, rezultat);
	return 0;
}
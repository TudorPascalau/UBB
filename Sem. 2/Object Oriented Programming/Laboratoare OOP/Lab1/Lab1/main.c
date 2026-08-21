#include <stdio.h>

int main()

{
	int n;
	double e;
	double s = 0;

	printf("Introduceti numarul de elemente: ");
	scanf_s("%d", &n);

	for (int i = 0; i < n; i++)
	{
		printf("Introduceti elementul urmator din sir: ");
		scanf_s("%lf", &e);

		s = s + e;
	}

	printf("Suma celor %d numere este %.2f\n", n, s);
	return 0;
}
/// Pe data viitoare problema 9 lab01
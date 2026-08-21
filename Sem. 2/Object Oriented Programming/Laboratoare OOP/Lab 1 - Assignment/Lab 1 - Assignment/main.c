/*
* Citeste un sir de numere naturale nenule terminat cu 0 si determina
    numarul cifrelor 0 in care se termina numarul produs al numerelor citite.
*/

#include <stdio.h>

void print_menu()
/*
* Functie care afiseaza meniul aplicatiei
* pre: - 
* post: se afiseaza meniul aplicatiei
*/
{
	printf("Meniu aplicatie laborator 01\n");
	printf("-----------------------------\n");
	printf("1. Citire sir de numere si determinarea numarului de 0-uri finale ale produsului\n");
	printf("2. Genereaza numere prime mai mici decat un numar natural dat\n");
	printf("0. Iesire\n");

}

char get_option()
/*
* Functie care citeste optiunea introdusa de utilizator
* pre: -
* post: se returneaza optiunea introdusa de utilizator
*/
{
	char line[64];
    printf(">>> ");
	scanf_s(" %s", line, 64);
	char x = getchar(); // consumam newline-ul ramas in buffer
	return line[0];
}

int divizori_2(int x)
/*
* Functie care determina numarul de divizori 2 ai unui numar
* param x: numarul pentru care se determina numarul de divizori 2
* pre: x este un numar natural nenul
* post: se returneaza numarul de divizori 2 ai numarului x
*/
{
	int count = 0;
	while (x % 2 == 0)
	{
		count++;
		x /= 2;
	}
	return count;

}

int divizori_5(int x)
/*
* Functie care determina numarul de divizori 5 ai unui numar
* param x: numarul pentru care se determina numarul de divizori 5
* pre: x este un numar natural nenul
* post: se returneaza numarul de divizori 5 ai numarului x
*/
{
	int count = 0;
	while (x % 5 == 0)
	{
		count++;
		x /= 5;
	}
	return count;

}

int verificare_numar(int x)
/*
* Functie care verifica daca un numar este natural nenul
* param x: numarul care se verifica
* pre: x este un numar
* post: returneaza 1 daca x este un numar natural nenul, 
		altfel se afiseaza un mesaj de eroare si se returneaza 0
*/
{
	if (x != (int)x || x < 0)
	{
		printf("Eroare: numarul introdus nu este un numar natural nenul!\n");
		return 0 ;
	}

	return 1;
}


void determinare_sir()
/*
* Functie care citeste un sir de numere naturale nenule terminat cu 0 si determina
	numarul cifrelor 0 in care se termina numarul produs al numerelor citite.
* pre: numerele citite sunt numere naturale nenule, iar sirul se termina cu 0
* post: se afiseaza numarul cifrelor 0 in care se termina numarul produs al numerelor citite
*		se afiseaza mesaj de eroare daca unul dintre numerele citite nu este natural nenul
*/
{
	int x;
	int count_2 = 0;
	int count_5 = 0;
	int nr_cif_0;

	printf("Introduceti un sir de numere naturale nenule terminat cu 0:\n");
	scanf_s("%d", &x);

	while (x != 0)
	{
		int verif = verificare_numar(x);
		if (verif == 0) return;

		count_2 = count_2 + divizori_2(x);
		count_5 = count_5 + divizori_5(x);

		scanf_s("%d", &x);
	}

	if (count_2 <= count_5) nr_cif_0 = count_2;
	else nr_cif_0 = count_5;

	printf("Numarul de cifre 0 in care se termina numarul produs al numerelor citite este: %d\n", nr_cif_0);
}

int prim(int x)
/*
*	Functie care verifica daca un numar este prim
*	param x: numarul care se verifica
*	pre: x este un numar natural
*	post: returneaza 1 daca x este prim, altfel returneaza 0
*/
{
	if(x < 2) return 0;
	for(int i = 2; i <= x / 2; i++)
		if(x%i == 0) return 0;
	return 1;
}

void genereaza_prime(int n)
/*
* Functie care genereaza numere prime mai mici decat un numar natural dat
* param n: numarul natural dat
* pre: n este un numar natural
* post: se afiseaza numerele prime mai mici decat n
*/
{
	for(int i=1; i<n; i++)
		if (prim(i)) printf("%d ", i);
	printf("\n");
}

int main()
{
	while(1)
	{
		print_menu();
		char option = get_option();
		int n;
		switch (option)
		{
			case '1':
				determinare_sir();
				break;

			case '2':
				printf("Introduceti nr. natural n: ");
				scanf_s("%d", &n);
				genereaza_prime(n);
				break;

			case '0':
				printf("La revedere!\n");
				return 0;


			default:
				printf("Optiune invalida! Incercati din nou.\n");
				break;
		}
	}

	return 0;
}
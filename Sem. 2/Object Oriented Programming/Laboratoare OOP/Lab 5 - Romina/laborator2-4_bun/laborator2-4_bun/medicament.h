#ifndef MEDICAMENT_H_
#define MEDICAMENT_H_

typedef struct {
	int cod;
	char* nume;
	float concentratie;
	int cantitate;
} Medicament;

/*
* Creaza un nou medicament.
* cod - codul medicamentului, int, unic
* nume - numele medicamentului, string
* concentratie - concentratia medicamentului, float
* cantitate - calitatea medicamentului, int, > 0
* RETURN: un nou medicament creat cu datele primite ca parametru
*/
Medicament* creeaza_medicament(int cod, char* nume, float concentratie, int cantitate);

/*
* Eliberează memoria ocupată de un medicament : numele și structura.
*/
void distruge_medicament(Medicament* m);

// Tipul de funcție care compară două medicamente
typedef int (*FunctieComparare)(Medicament* m1, Medicament* m2, int sens);

#endif 

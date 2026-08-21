#ifndef MEDICAMENT_H_
#define MEDICAMENT_H_

typedef struct {
    int cod;
    char* nume;
    float concentratie;
    int cantitate;
} Medicament;

/*
* Creeaza un medicament.
* param cod: codul medicamentului
* param nume: numele medicamentului
* param concentratie: concentratia medicamentului
* param cantitate: cantitatea medicamentului
* preconditii: nume != NULL
* postconditii: se creeaza un nou obiect de tip Medicament, alocat dinamic, care contine
*               valorile primite ca parametri; campul nume este copiat in memorie proprie
* return: pointer catre medicamentul creat, sau NULL daca alocarea memoriei a esuat
*/
Medicament* creeaza_medicament(int cod, const char* nume, float concentratie, int cantitate);

/*
* Creeaza o copie profunda a unui medicament.
* param m: medicamentul care se copiaza
* preconditii: m != NULL
* postconditii: se creeaza un nou obiect de tip Medicament, independent de cel primit,
*               cu aceleasi campuri ca medicamentul sursa
* return: pointer catre copia creata, sau NULL daca m == NULL sau daca alocarea a esuat
*/
Medicament* copiaza_medicament(const Medicament* m);

/*
* Distruge un medicament si elibereaza memoria asociata.
* param m: medicamentul de distrus
* preconditii: -
* postconditii: memoria ocupata de medicament si de campurile sale alocate dinamic este eliberata;
*               daca m == NULL, functia nu produce niciun efect
*/
void distruge_medicament(Medicament* m);

/*
* Returneaza codul medicamentului.
* param m: medicamentul pentru care se cere codul
* preconditii: m != NULL
* postconditii: se returneaza codul medicamentului
* return: codul medicamentului
*/
int get_cod(const Medicament* m);

/*
* Returneaza numele medicamentului.
* param m: medicamentul pentru care se cere numele
* preconditii: m != NULL
* postconditii: se returneaza adresa sirului de caractere asociat numelui medicamentului
* return: numele medicamentului
*/
const char* get_nume(const Medicament* m);

/*
* Returneaza concentratia medicamentului.
* param m: medicamentul pentru care se cere concentratia
* preconditii: m != NULL
* postconditii: se returneaza concentratia medicamentului
* return: concentratia medicamentului
*/
float get_concentratie(const Medicament* m);

/*
* Returneaza cantitatea medicamentului.
* param m: medicamentul pentru care se cere cantitatea
* preconditii: m != NULL
* postconditii: se returneaza cantitatea medicamentului
* return: cantitatea medicamentului
*/
int get_cantitate(const Medicament* m);

/*
* Tip de functie pentru compararea a doua medicamente.
* param m1: primul medicament
* param m2: al doilea medicament
* param sens: sensul compararii
* preconditii: m1 != NULL, m2 != NULL
* postconditii: functia de comparare intoarce o valoare conform criteriului ales de implementare
* return: rezultat al compararii
*/
typedef int (*FunctieComparare)(const Medicament* m1, const Medicament* m2, int sens);

/*
* Functii folosite doar in teste pentru a forta esecul alocarii.
*/
void setForceMedicamentAllocFail(int value);
void setForceNumeAllocFail(int value);

#endif
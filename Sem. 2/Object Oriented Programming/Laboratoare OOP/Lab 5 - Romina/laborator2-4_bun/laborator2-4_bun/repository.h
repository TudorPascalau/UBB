#ifndef REPOSITORY_H_
#define REPOSITORY_H_
#include "medicament.h"

typedef struct {
	Medicament* medicamente;
	int lungime;
	int memorie_alocata;
} RepoFarmacie;

// Initializeaza repository ul de medicamente
void initRepo(RepoFarmacie* repo);

// Elibereaza memoria ocupata de repository ul de medicamente
void distrugeRepo(RepoFarmacie* repo);

/*
* Adauga un medicament in repository
* repo - pointer la repository ul de medicamente
* m - medicamentul care se adauga
* post-conditii: medicamentul m a fost adaugat in repository ul repo, daca acesta nu era plin
* pre-conditii: repo nu este NULL, m este un medicament valid
* RETURN: 1 daca medicamentul a fost adaugat cu succes, 0 daca repository ul este plin
*/
int adauga_medicament(RepoFarmacie* repo, Medicament m);

/*
* Cauta un medicament dupa cod
* repo - pointer la repository ul de medicamente
* cod - codul medicamentului cautat
* post-conditii: daca exista un medicament cu codul dat, se returneaza adresa acestuia, altfel se returneaza NULL
* pre-conditii: repo nu este NULL, cod este un numar intreg
* RETURN: adresa medicamentului gasit, sau NULL daca nu s-a gasit niciun medicament cu codul dat
*/
Medicament* gaseste_medicament_cod(RepoFarmacie* repo, int cod);

/*
* Se sterge un tip de medicament din stoc dupa codul acestuia
* repo - pointer la repository ul de medicamente
* cod - codul medicamentului de sters
* post-conditii: daca exista un medicament cu codul dat, acesta a fost sters din repository ul repo, iar lungimea repository ului a fost actualizata, altfel repository ul ramane neschimbat
* pre-conditii: repo nu este NULL, cod este un numar intreg
* RETURN: 1 daca medicamentul a fost sters cu succes, 0 daca nu s-a gasit niciun medicament cu codul dat
*/
int sterge_medicament(RepoFarmacie* repo, int cod);

#endif
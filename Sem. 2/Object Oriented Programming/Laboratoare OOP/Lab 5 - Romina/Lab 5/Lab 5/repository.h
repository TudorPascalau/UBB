#ifndef REPOSITORY_H_
#define REPOSITORY_H_

#include "lista.h"
#include "medicament.h"

typedef struct {
    List medicamente;
} Repository;

/*
* Creeaza un repository gol de medicamente.
* preconditii: -
* postconditii: se creeaza un repository care contine o lista vida de medicamente;
*               lista este configurata sa foloseasca functiile de copiere si distrugere
*               specifice tipului Medicament
* return: repository-ul creat
*/
Repository createRepository();

/*
* Distruge un repository.
* param repo: repository-ul de distrus
* preconditii: -
* postconditii: sunt distruse toate medicamentele din repository si se elibereaza memoria
*               asociata listei interne; daca repo == NULL, functia nu produce niciun efect
*/
void destroyRepository(Repository* repo);

/*
* Adauga un medicament in repository.
* param repo: repository-ul in care se adauga
* param m: medicamentul de adaugat
* preconditii: repo != NULL, m != NULL
* postconditii: daca nu exista deja un medicament cu acelasi cod, in repository se adauga
*               o copie a medicamentului, iar dimensiunea creste cu 1; daca exista deja un
*               medicament cu acelasi cod sau daca apare o eroare de memorie, repository-ul
*               ramane neschimbat
* return: 1 daca adaugarea s-a realizat cu succes, 0 altfel
*/
int repoAddMedicament(Repository* repo, const Medicament* m);

/*
* Sterge medicamentul cu codul dat din repository.
* param repo: repository-ul din care se sterge
* param cod: codul medicamentului de sters
* preconditii: repo != NULL
* postconditii: daca exista un medicament cu codul dat, acesta este sters, iar dimensiunea
*               repository-ului scade cu 1; daca nu exista, repository-ul ramane neschimbat
* return: 1 daca stergerea s-a realizat cu succes, 0 altfel
*/
int repoDeleteMedicament(Repository* repo, int cod);

/*
* Actualizeaza un medicament existent din repository.
* param repo: repository-ul in care se face actualizarea
* param mNou: medicamentul cu noile date
* preconditii: repo != NULL, mNou != NULL
* postconditii: daca exista un medicament cu acelasi cod ca mNou, acesta este inlocuit cu
*               o copie a lui mNou; daca nu exista sau daca apare o eroare de memorie,
*               repository-ul ramane neschimbat
* return: 1 daca actualizarea s-a realizat cu succes, 0 altfel
*/
int repoUpdateMedicament(Repository* repo, const Medicament* mNou);

/*
* Cauta pozitia unui medicament dupa cod.
* param repo: repository-ul in care se cauta
* param cod: codul cautat
* preconditii: repo != NULL
* postconditii: se determina pozitia medicamentului cu codul dat, daca acesta exista
* return: pozitia medicamentului, sau -1 daca nu exista sau daca repo == NULL
*/
int repoFindPositionByCod(const Repository* repo, int cod);

/*
* Returneaza medicamentul de pe o anumita pozitie.
* param repo: repository-ul din care se citeste
* param pos: pozitia elementului
* preconditii: repo != NULL
* postconditii: daca pozitia este valida, se returneaza pointer catre medicamentul de pe
*               acea pozitie; altfel se returneaza NULL
* return: pointer la medicament, sau NULL daca pozitia este invalida
*/
Medicament* repoGetMedicament(const Repository* repo, int pos);

/*
* Returneaza numarul de medicamente din repository.
* param repo: repository-ul pentru care se cere dimensiunea
* preconditii: -
* postconditii: se returneaza numarul de medicamente din repository; daca repo == NULL,
*               se returneaza 0
* return: dimensiunea repository-ului
*/
int repoSize(const Repository* repo);

/*
* Returneaza lista interna a repository-ului.
* param repo: repository-ul pentru care se cere lista interna
* preconditii: repo != NULL
* postconditii: se returneaza adresa listei interne de medicamente
* return: pointer la lista interna, sau NULL daca repo == NULL
*/
List* repoGetAll(Repository* repo);

/*
* Creeaza o copie profunda a unui repository.
* param repo: repository-ul sursa
* preconditii: repo != NULL
* postconditii: se creeaza un repository nou, independent de cel sursa, care contine
*               copii ale tuturor medicamentelor din repository-ul sursa
* return: pointer la copia repository-ului, sau NULL daca repo == NULL sau daca alocarea esueaza
*/
Repository* copyRepository(const Repository* repo);

/*
* Distruge un repository alocat dinamic.
* param repo: pointer generic la repository-ul de distrus
* preconditii: -
* postconditii: daca repo != NULL, se distruge repository-ul si se elibereaza memoria structurii;
*               daca repo == NULL, functia nu produce niciun efect
*/
void destroyRepositoryPointer(void* repo);

void setForceRepositoryAllocFail(int value);
void setForceRepoGetMedicamentFail(int value);
void setForceRepoDeleteFail(int value);

#endif
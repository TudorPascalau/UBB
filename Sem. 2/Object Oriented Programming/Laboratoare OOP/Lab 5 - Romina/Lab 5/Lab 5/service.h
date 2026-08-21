#ifndef SERVICE_H_
#define SERVICE_H_

#include "repository.h"
#include "validare.h"

#define SERVICE_SUCCESS 0
#define SERVICE_NULL_ERROR 1
#define SERVICE_MEMORY_ERROR 2
#define SERVICE_VALIDATION_ERROR 3
#define SERVICE_NOT_FOUND_ERROR 4
#define SERVICE_UNDO_EMPTY 5
#define SERVICE_CONFLICT_ERROR 6

#define SERVICE_ADD_CREATED 1
#define SERVICE_ADD_UPDATED 2

typedef struct {
    Repository repo;
    List undoList;
} Service;

/*
* Creeaza un service pentru gestiunea medicamentelor.
* preconditii: -
* postconditii: se creeaza un service cu repository vid si lista de undo vida
* return: service-ul creat
*/
Service createService(void);

/*
* Distruge un service.
* param s: service-ul de distrus
* preconditii: -
* postconditii: se elibereaza memoria asociata repository-ului si listei de undo;
*               daca s == NULL, functia nu produce niciun efect
*/
void destroyService(Service* s);

/*
* Adauga un medicament.
* Daca exista deja un medicament cu codul dat, se actualizeaza cantitatea acestuia.
* param s: service-ul
* param cod: codul medicamentului
* param nume: numele medicamentului
* param concentratie: concentratia medicamentului
* param cantitate: cantitatea medicamentului
* preconditii: s != NULL, nume != NULL
* postconditii: daca datele sunt valide:
*               - se adauga un medicament nou daca nu exista codul
*               - se actualizeaza cantitatea daca exista deja codul
*               in ambele cazuri, starea anterioara este salvata pentru undo;
*               altfel, starea ramane neschimbata
* return: SERVICE_ADD_CREATED daca s-a adaugat un medicament nou,
*         SERVICE_ADD_UPDATED daca s-a actualizat cantitatea unui medicament existent,
*         SERVICE_VALIDATION_ERROR daca datele sunt invalide,
*         SERVICE_MEMORY_ERROR daca apare o eroare de memorie,
*         SERVICE_NULL_ERROR daca s == NULL sau nume == NULL
*/
int serviceAddMedicament(Service* s, int cod, const char* nume, float concentratie, int cantitate);

/*
* Actualizeaza un medicament existent dupa cod.
* Se modifica numele si concentratia, pastrand cantitatea existenta.
* param s: service-ul
* param cod: codul medicamentului
* param numeNou: noul nume
* param concentratieNoua: noua concentratie
* preconditii: s != NULL, numeNou != NULL
* postconditii: daca medicamentul exista si noile date sunt valide, numele si concentratia
*               sunt actualizate, iar starea anterioara este salvata pentru undo;
*               altfel, starea ramane neschimbata
* return: SERVICE_SUCCESS daca actualizarea s-a realizat,
*         SERVICE_NOT_FOUND_ERROR daca nu exista medicamentul,
*         SERVICE_VALIDATION_ERROR daca datele sunt invalide,
*         SERVICE_MEMORY_ERROR daca apare o eroare de memorie,
*         SERVICE_NULL_ERROR daca s == NULL sau numeNou == NULL
*/
int serviceUpdateMedicament(Service* s, int cod, const char* numeNou, float concentratieNoua);

/*
* Sterge un medicament dupa cod.
* param s: service-ul
* param cod: codul medicamentului de sters
* preconditii: s != NULL
* postconditii: daca medicamentul exista, acesta este sters, iar starea anterioara este
*               salvata pentru undo; altfel, starea ramane neschimbata
* return: SERVICE_SUCCESS daca stergerea s-a realizat,
*         SERVICE_NOT_FOUND_ERROR daca nu exista medicamentul,
*         SERVICE_MEMORY_ERROR daca apare o eroare de memorie,
*         SERVICE_NULL_ERROR daca s == NULL
*/
int serviceDeleteMedicament(Service* s, int cod);

/*
* Executa operatia de undo.
* param s: service-ul
* preconditii: s != NULL
* postconditii: daca exista o stare salvata in lista de undo, repository-ul curent este
*               inlocuit cu ultima stare salvata; altfel, starea ramane neschimbata
* return: SERVICE_SUCCESS daca undo s-a realizat,
*         SERVICE_UNDO_EMPTY daca nu exista undo,
*         SERVICE_NULL_ERROR daca s == NULL
*/
int serviceUndo(Service* s);

/*
* Returneaza lista curenta de medicamente.
* param s: service-ul
* preconditii: -
* postconditii: se returneaza lista interna a repository-ului curent;
*               daca s == NULL, se returneaza NULL
* return: pointer la lista curenta de medicamente
*/
List* serviceGetAll(Service* s);

/*
* Returneaza numarul de medicamente din service.
* param s: service-ul
* preconditii: -
* postconditii: se returneaza numarul de medicamente din repository-ul curent;
*               daca s == NULL, se returneaza 0
* return: dimensiunea curenta
*/
int serviceSize(const Service* s);

/*
* Compara doua medicamente dupa nume.
* param m1: primul medicament
* param m2: al doilea medicament
* param sens: 1 pentru crescator, 2 pentru descrescator
* preconditii: m1 != NULL, m2 != NULL
* postconditii: se determina daca ordinea celor doua medicamente trebuie inversata
*               pentru sortarea dupa nume, in sensul dat
* return: 1 daca elementele trebuie interschimbate, 0 altfel
*/
int comparaNume(const Medicament* m1, const Medicament* m2, int sens);

/*
* Compara doua medicamente dupa cantitate.
* param m1: primul medicament
* param m2: al doilea medicament
* param sens: 1 pentru crescator, 2 pentru descrescator
* preconditii: m1 != NULL, m2 != NULL
* postconditii: se determina daca ordinea celor doua medicamente trebuie inversata
*               pentru sortarea dupa cantitate, in sensul dat
* return: 1 daca elementele trebuie interschimbate, 0 altfel
*/
int comparaCantitate(const Medicament* m1, const Medicament* m2, int sens);

/*
* Creeaza o lista sortata pe baza unui comparator.
* param s: service-ul
* param listaSortata: lista destinatie
* param functieComp: functia de comparare
* param sens: 1 pentru crescator, 2 pentru descrescator
* preconditii: s != NULL, listaSortata != NULL, functieComp != NULL
* postconditii: in listaSortata se pune o copie a listei curente, sortata conform
*               comparatorului si sensului date; lista curenta din service nu se modifica
* return: SERVICE_SUCCESS daca operatia s-a realizat,
*         SERVICE_MEMORY_ERROR daca apare o eroare de memorie,
*         SERVICE_NULL_ERROR daca un parametru obligatoriu este NULL
*/
int serviceSortGeneral(const Service* s, List* listaSortata, FunctieComparare functieComp, int sens);

/*
* Filtreaza medicamentele care au cantitatea mai mica decat o valoare data.
* param s: service-ul
* param listaFiltrata: lista destinatie
* param valoareLimita: valoarea limita pentru cantitate
* preconditii: s != NULL, listaFiltrata != NULL
* postconditii: in listaFiltrata se pune o lista noua cu toate medicamentele care au
*               cantitatea mai mica decat valoareLimita
* return: SERVICE_SUCCESS daca operatia s-a realizat,
*         SERVICE_MEMORY_ERROR daca apare o eroare de memorie,
*         SERVICE_NULL_ERROR daca un parametru obligatoriu este NULL
*/
int serviceFilterStockLessThan(const Service* s, List* listaFiltrata, int valoareLimita);

/*
* Filtreaza medicamentele care au numele ce incepe cu o litera data.
* param s: service-ul
* param listaFiltrata: lista destinatie
* param litera: litera de inceput
* preconditii: s != NULL, listaFiltrata != NULL
* postconditii: in listaFiltrata se pune o lista noua cu toate medicamentele care au
*               numele ce incepe cu litera data
* return: SERVICE_SUCCESS daca operatia s-a realizat,
*         SERVICE_MEMORY_ERROR daca apare o eroare de memorie,
*         SERVICE_NULL_ERROR daca un parametru obligatoriu este NULL
*/
int serviceFilterNameStartsWith(const Service* s, List* listaFiltrata, char litera);

/*
* Filtreaza medicamentele care au concentratia mai mare decat o valoare data.
* param s: service-ul
* param listaFiltrata: lista destinatie
* param valoareLimita: valoarea limita pentru concentratie
* preconditii: s != NULL, listaFiltrata != NULL
* postconditii: in listaFiltrata se pune o lista noua cu toate medicamentele care au
*               concentratia mai mare decat valoareLimita
* return: SERVICE_SUCCESS daca operatia s-a realizat,
*         SERVICE_MEMORY_ERROR daca apare o eroare de memorie,
*         SERVICE_NULL_ERROR daca un parametru obligatoriu este NULL
*/
int serviceFilterConcentrationGreaterThan(const Service* s, List* listaFiltrata, float valoareLimita);

#endif
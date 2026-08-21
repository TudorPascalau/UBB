#ifndef SERVICE_H_
#define SERVICE_H_
#include "repository.h"

/*
* Adauga un medicament
* Daca exista deja un medicament cu codul dat, se actualizeaza cantitatea acestuia.
* cod - codul medicamentului, int, unic
* nume - numele medicamentului, string
* concentratie - concentratia medicamentului, float
* cantitate - calitatea medicamentului, int, > 0
* pre-conditii: repo nu este NULL, cod este un numar intreg, nume este un string valid, concentratie este un numar float valid, cantitate este un numar int valid
* post-conditii: daca exista deja un medicament cu codul dat, cantitatea acestuia a fost actualizata cu cantitatea data, altfel a fost adaugat un nou medicament in repository ul repo
* RETURN: 2 daca medicamentul a fost actualizat cu succes, 1 daca medicamentul a fost adaugat cu succes, 0 daca stocul este plin
*/
int s_adauga_medicament(RepoFarmacie* repo, int cod, char* nume, float concentratie, int cantitate);

/*
* Lista auxiliara cu toate medicamentele din farmacie
* pre-conditii: repo nu este NULL
* post-conditii: se returneaza o lista auxiliara care contine toate medicamentele din repository ul repo
* RETURN: o lista auxiliara care contine toate medicamentele din repository ul repo
*/
RepoFarmacie* s_get_toate_medicamentele(RepoFarmacie* repo);


/*
* Actualizeaza un medicament gasit dupa codul sau.
* cod - codul medicamentului de actualizat, int
* nume_nou - noul nume al medicamentului, string
* concentratie_noua - noua concentratie a medicamentului, float
* pre-conditii: repo nu este NULL, cod este un numar intreg, nume_nou este un string valid, concentratie_noua este un numar float valid
* post-conditii: daca exista un medicament cu codul dat, numele si concentratia acestuia au fost actualizate cu valorile date, altfel repository ul ramane neschimbat
* RETURN : 1 daca medicamentul a fost actualizat cu succes, 0 daca nu s-a gasit niciun medicament cu codul dat
*/
int s_actualizeaza_medicament(RepoFarmacie* repo, int cod, char* nume_nou, float concentratie_noua);


/*
* Sterge un medicament gasit dupa codul sau.
* cod - codul medicamentului de sters, int
* pre-conditii: repo nu este NULL, cod este un numar intreg
* post-conditii: daca exista un medicament cu codul dat, acesta a fost sters din repository ul repo, iar lungimea repository ului a fost actualizata, altfel repository ul ramane neschimbat
* RETURN : 1 daca medicamentul a fost sters cu succes, 0 daca nu s-a gasit niciun medicament cu codul dat
*/
int s_sterge_medicament(RepoFarmacie* repo, int cod);


/*
* Sorteaza medicamentele dupa un criteriu : sau nume sau cantitate, intr un anumit sens : sau crescator sau descrescator
* criteriu - criteriul dupa care se sorteaza, int (1 pentru nume, 2 pentru cantitate)
* sens - sensul de sortare, int (1 pentru crescator, 2 pentru descrescator)
* pre-conditii: repo nu este NULL, criteriu este 1 sau 2, sens este 1 sau 2
* post-conditii: se returneaza o lista auxiliara care contine toate medicamentele din repository ul repo, sortate dupa criteriul si sensul dat
* RETURN: o lista auxiliara care contine toate medicamentele din repository ul repo, sortate dupa criteriul si sensul dat
*/
// void s_sorteaza_medicamente(RepoFarmacie* repo, RepoFarmacie* copie_dest, int criteriu, int sens);

/*
* Filtreaza medicamentele care au cantitatea mai mica decat o valoare data
* valoare_limita - valoarea limita pentru cantitate, int
* pre-conditii: repo nu este NULL, valoare_limita este un numar intreg
* post-conditii: se returneaza o lista auxiliara care contine toate medicamentele din repository ul repo care au cantitatea mai mica decat valoare_limita
* RETURN: o lista auxiliara care contine toate medicamentele din repository ul repo care au cantitatea mai mica decat valoare_limita
*/
void s_filtreaza_stoc_mai_mic(RepoFarmacie* repo, RepoFarmacie* lista_filtrata, int valoare_limita);

/*
* Filtreaza medicamentele care au numele care incepe cu o litera data
* litera - litera dupa care se filtreaza, char
* pre-conditii: repo nu este NULL, litera este un caracter valid
* post-conditii: se returneaza o lista auxiliara care contine toate medicamentele din repository ul repo care au numele care incepe cu litera data
* RETURN: o lista auxiliara care contine toate medicamentele din repository ul repo care au numele care incepe cu litera data
*/
void s_filtreaza_medicamente_litera_data(RepoFarmacie* repo, RepoFarmacie* lista_filtrata, char litera);

int comparaCantitate(Medicament* m1, Medicament* m2, int sens);

int comparaNume(Medicament* m1, Medicament* m2, int sens);

void s_sorteaza_general(RepoFarmacie* repo, RepoFarmacie* copie_dest, FunctieComparare functieComp, int sens);

#endif
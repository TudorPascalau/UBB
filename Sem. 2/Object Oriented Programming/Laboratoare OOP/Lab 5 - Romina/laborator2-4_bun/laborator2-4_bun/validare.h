#ifndef VALIDARE_H_
#define VALIDARE_H_
#include "medicament.h"

/*
* Valideaza un medicament.
* RETURN: 0 daca medicamentul este valid, codul erorii in caz contrar:
* 1 - codul medicamentului este negativ sau zero
* 2 - numele medicamentului este vid
* 3 - concentratia medicamentului este negativa sau zero
* 4 - cantitatea medicamentului este negativa sau zero
*/
int valideaza_medicament(Medicament m);

#endif

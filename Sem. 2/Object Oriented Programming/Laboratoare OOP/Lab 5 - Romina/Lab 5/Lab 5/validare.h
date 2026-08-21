#ifndef VALIDARE_H_
#define VALIDARE_H_

#include "medicament.h"

/*
* Valideaza un medicament conform regulilor aplicatiei.
* param m: medicamentul de validat
* preconditii: -
* postconditii: se verifica daca medicamentul respecta regulile de validare:
*               cod > 0, nume diferit de NULL si nevid, concentratie > 0, cantitate > 0
* return: 0 daca medicamentul este valid;
*         1 daca medicamentul este NULL;
*         2 daca codul este invalid;
*         3 daca numele este invalid;
*         4 daca concentratia este invalida;
*         5 daca cantitatea este invalida
*/
int valideaza_medicament(const Medicament* m);

#endif
#include "medicament.h"
#include <string.h>
#include <stdlib.h>

// Variabile globale pentru simularea erorilor (Code Coverage)
int forteaza_eroare_m = 0;
int forteaza_eroare_nume = 0;

Medicament* creeaza_medicament(int cod, char* nume, float concentratie, int cantitate) {
    if (nume == NULL) return NULL;

    // 1. Alocăm întâi numele separat într-un buffer auxiliar
    char* nume_aux = NULL;
    if (forteaza_eroare_nume != 1) {
        int nrCaractere = (int)strlen(nume) + 1;
        nume_aux = (char*)malloc(nrCaractere * sizeof(char));
        if (nume_aux != NULL) {
            strcpy_s(nume_aux, nrCaractere, nume);
        }
    }

    // 2. Alocăm structura medicamentului
    Medicament* m = NULL;
    if (forteaza_eroare_m != 1) {
        m = (Medicament*)malloc(sizeof(Medicament));
    }

    // 3. Gestionare eșecuri (dacă una din alocări a picat, curățăm tot)
    if (nume_aux == NULL) {
        if (m != NULL) free(m);
        return NULL;
    }
    if (m == NULL) {
        if (nume_aux != NULL) free(nume_aux);
        return NULL;
    }

    // 4. Asamblare obiect
    m->cod = cod;
    m->nume = nume_aux;
    m->concentratie = concentratie;
    m->cantitate = cantitate;

    return m;
}

void distruge_medicament(Medicament* m) {
    if (m == NULL) return;
    if (m->nume != NULL) {
        free(m->nume);
    }
    free(m);
}
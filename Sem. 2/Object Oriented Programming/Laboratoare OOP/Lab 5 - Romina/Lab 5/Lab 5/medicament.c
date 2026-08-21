#include "medicament.h"
#include <stdlib.h>
#include <string.h>

static int forceMedicamentAllocFail = 0;
static int forceNumeAllocFail = 0;

void setForceMedicamentAllocFail(int value) {
	forceMedicamentAllocFail = value;
}

void setForceNumeAllocFail(int value) {
	forceNumeAllocFail = value;
}

Medicament* creeaza_medicament(int cod, const char* nume, float concentratie, int cantitate) {
    if (nume == NULL) {
        return NULL;
    }

    if (forceMedicamentAllocFail) {
        return NULL;
    }

    Medicament* m = (Medicament*)malloc(sizeof(Medicament));
    //if (m == NULL) {
    //    return NULL;
    //}

    int lungime = (int)strlen(nume) + 1;

    if (forceNumeAllocFail) {
        free(m);
        return NULL;
    }

    m->nume = (char*)malloc(lungime * sizeof(char));
    //if (m->nume == NULL) {
    //    free(m);
    //    return NULL;
    //}


    strcpy_s(m->nume, lungime, nume);
    m->cod = cod;
    m->concentratie = concentratie;
    m->cantitate = cantitate;

    return m;
}

Medicament* copiaza_medicament(const Medicament* m) {
	if (m == NULL) {
		return NULL;
	}

	return creeaza_medicament(m->cod, m->nume, m->concentratie, m->cantitate);
}

void distruge_medicament(Medicament* m) {
	//if (m == NULL) {
	//	return;
	//}

	free(m->nume);
	free(m);
}

int get_cod(const Medicament* m) {
	return m->cod;
}

const char* get_nume(const Medicament* m) {
	return m->nume;
}

float get_concentratie(const Medicament* m) {
	return m->concentratie;
}

int get_cantitate(const Medicament* m) {
	return m->cantitate;
}
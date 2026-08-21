#include "service.h"
#include <stdlib.h>
#include <string.h>

int s_adauga_medicament(RepoFarmacie* repo, int cod, char* nume, float concentratie, int cantitate) {
    Medicament* med_existent = gaseste_medicament_cod(repo, cod);
	// exista un medicament cu codul dat, actualizam cantitatea acestuia adunand la cantitatea existenta 
    if (med_existent != NULL) {
        med_existent->cantitate += cantitate;
        return 2;
    }

    Medicament* med_nou = creeaza_medicament(cod, nume, concentratie, cantitate);
    if (med_nou == NULL) return 0;

    int rez = adauga_medicament(repo, *med_nou);
    distruge_medicament(med_nou); // Repo are acum copia lui, deci îl putem șterge pe acesta
    return rez; // adaug cu succes 
}

int s_actualizeaza_medicament(RepoFarmacie* repo, int cod, char* nume_nou, float concentratie_noua) {
    Medicament* m = gaseste_medicament_cod(repo, cod);
    if (m == NULL) return 0;

    // Eliberăm numele vechi și alocăm spațiu pentru cel nou (Safe Update)
    free(m->nume);
    int len = (int)strlen(nume_nou) + 1;
    m->nume = malloc(len * sizeof(char));
    if (m->nume != NULL) {
        strcpy_s(m->nume, len, nume_nou);
    }
    m->concentratie = concentratie_noua;
    return 1;
}

int s_sterge_medicament(RepoFarmacie* repo, int cod) {
    return sterge_medicament(repo, cod);
}

void s_copiaza_repository(RepoFarmacie* sursa, RepoFarmacie* destinatie) {
    initRepo(destinatie);
    for (int i = 0; i < sursa->lungime; i++) {
        adauga_medicament(destinatie, sursa->medicamente[i]);
    }
}

/*
void s_sorteaza_medicamente(RepoFarmacie* repo, RepoFarmacie* copie_dest, int criteriu, int sens) {
    s_copiaza_repository(repo, copie_dest);

    for (int i = 0; i < copie_dest->lungime - 1; i++) {
        for (int j = i + 1; j < copie_dest->lungime; j++) {
            int comparare = 0;
            if (criteriu == 1) // Nume 
                comparare = strcmp(copie_dest->medicamente[i].nume, copie_dest->medicamente[j].nume);
            else if (criteriu == 2) // Cantitate
                comparare = (copie_dest->medicamente[i].cantitate > copie_dest->medicamente[j].cantitate) ? 1 : -1;

            if ((sens == 1 && comparare > 0) || (sens == 2 && comparare < 0)) {
                Medicament temp = copie_dest->medicamente[i];
                copie_dest->medicamente[i] = copie_dest->medicamente[j];
                copie_dest->medicamente[j] = temp;
            }
        }
    }
}
*/

void s_filtreaza_stoc_mai_mic(RepoFarmacie* repo, RepoFarmacie* lista_filtrata, int valoare_limita) {
    initRepo(lista_filtrata);
    for (int i = 0; i < repo->lungime; i++) {
        if (repo->medicamente[i].cantitate < valoare_limita) {
            adauga_medicament(lista_filtrata, repo->medicamente[i]);
        }
    }
}

void s_filtreaza_medicamente_litera_data(RepoFarmacie* repo, RepoFarmacie* lista_filtrata, char litera) {
    initRepo(lista_filtrata);
    for (int i = 0; i < repo->lungime; i++) {
        if (repo->medicamente[i].nume[0] == litera) {
            adauga_medicament(lista_filtrata, repo->medicamente[i]);
        }
    }
}

RepoFarmacie* s_get_toate_medicamentele(RepoFarmacie* repo) {
    return repo;
}

int comparaNume(Medicament* m1, Medicament* m2, int sens) {
    int rez = strcmp(m1->nume, m2->nume);
    if (sens == 1) // Crescator
        return rez > 0;
    else        // Descrescator
        return rez < 0;
}

int comparaCantitate(Medicament* m1, Medicament* m2, int sens) {
    if (sens == 1) // Crescator
        return m1->cantitate > m2->cantitate;
    else {         // Descrescator
        return m1->cantitate < m2->cantitate;
    }
}


void s_sorteaza_general(RepoFarmacie* repo, RepoFarmacie* copie_dest, FunctieComparare functieComp, int sens) {
    s_copiaza_repository(repo, copie_dest);

    for (int i = 0; i < copie_dest->lungime - 1; i++) {
        for (int j = i + 1; j < copie_dest->lungime; j++) {

            if (functieComp(&copie_dest->medicamente[i], &copie_dest->medicamente[j], sens)) {
                Medicament temp = copie_dest->medicamente[i];
                copie_dest->medicamente[i] = copie_dest->medicamente[j];
                copie_dest->medicamente[j] = temp;
            }
        }
    }
}
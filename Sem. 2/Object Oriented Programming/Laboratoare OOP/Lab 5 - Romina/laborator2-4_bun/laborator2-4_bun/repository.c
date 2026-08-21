#include "repository.h"
#include <stdlib.h>
#include <string.h>

void initRepo(RepoFarmacie* repo) {
    repo->lungime = 0;
    repo->memorie_alocata = 2;
    repo->medicamente = malloc(repo->memorie_alocata * sizeof(Medicament));
}

void distrugeRepo(RepoFarmacie* repo) {
    if (repo->medicamente == NULL) return;
    // Eliberăm numele fiecărui medicament din vector
    for (int i = 0; i < repo->lungime; i++) {
        if (repo->medicamente[i].nume != NULL) {
            free(repo->medicamente[i].nume);
        }
    }
    free(repo->medicamente);
    repo->medicamente = NULL;
    repo->lungime = 0;
    repo->memorie_alocata = 0;
}

void resize(RepoFarmacie* repo) {
    int newMemAlloc = repo->memorie_alocata * 2;
    Medicament* nElems = malloc(newMemAlloc * sizeof(Medicament));
    if (nElems == NULL) return;

    for (int i = 0; i < repo->lungime; i++) {
        nElems[i] = repo->medicamente[i]; // Transferăm structurile (shallow copy e ok pt mutare)
    }

    free(repo->medicamente); // Eliberăm doar vectorul vechi de structuri
    repo->medicamente = nElems;
    repo->memorie_alocata = newMemAlloc;
}

int adauga_medicament(RepoFarmacie* repo, Medicament m) {
    if (repo->lungime == repo->memorie_alocata)
        resize(repo);

    // DEEP COPY: Repository-ul își alocă propria memorie pentru nume
    Medicament copie;
    copie.cod = m.cod;
    copie.concentratie = m.concentratie;
    copie.cantitate = m.cantitate;

    int len = (int)strlen(m.nume) + 1;
    copie.nume = malloc(len * sizeof(char));
    if (copie.nume != NULL) {
        strcpy_s(copie.nume, len, m.nume);
    }

    repo->medicamente[repo->lungime] = copie;
    repo->lungime++;
    return 1;
}

Medicament* gaseste_medicament_cod(RepoFarmacie* repo, int cod) {
    for (int i = 0; i < repo->lungime; i++) {
        if (repo->medicamente[i].cod == cod)
            return &repo->medicamente[i];
    }
    return NULL;
}

int sterge_medicament(RepoFarmacie* repo, int cod) {
    int pozitie = -1;
    for (int i = 0; i < repo->lungime; i++) {
        if (repo->medicamente[i].cod == cod) {
            pozitie = i;
            break;
        }
    }

    if (pozitie == -1) return 0;

    // Eliberăm memoria numelui pentru elementul eliminat
    free(repo->medicamente[pozitie].nume);

    // Shiftăm restul elementelor
    for (int i = pozitie; i < repo->lungime - 1; i++) {
        repo->medicamente[i] = repo->medicamente[i + 1];
    }

    repo->lungime--;
    return 1;
}
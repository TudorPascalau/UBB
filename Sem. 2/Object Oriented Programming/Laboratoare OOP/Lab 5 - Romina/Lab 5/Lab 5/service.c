#include "service.h"

#include <stdlib.h>
#include <string.h>

static int saveUndo(Service* s) {
    if (s == NULL) {
        return 0;
    }

    return addElem(&s->undoList, &s->repo);
}

static void initResultList(List* l) {
    *l = createList((CopyFunction)copiaza_medicament, (DestroyFunction)distruge_medicament);
}

Service createService(void) {
    Service s;
    s.repo = createRepository();
    s.undoList = createList((CopyFunction)copyRepository, destroyRepositoryPointer);
    return s;
}

void destroyService(Service* s) {
    if (s == NULL) {
        return;
    }

    destroyRepository(&s->repo);
    destroyList(&s->undoList);
}

int serviceAddMedicament(Service* s, int cod, const char* nume, float concentratie, int cantitate) {
    if (s == NULL || nume == NULL) {
        return SERVICE_NULL_ERROR;
    }

    Medicament* m = creeaza_medicament(cod, nume, concentratie, cantitate);
    if (m == NULL) {
        return SERVICE_MEMORY_ERROR;
    }

    if (valideaza_medicament(m) != 0) {
        distruge_medicament(m);
        return SERVICE_VALIDATION_ERROR;
    }

    int poz = repoFindPositionByCod(&s->repo, cod);
    if (poz != -1) {
        Medicament* existent = repoGetMedicament(&s->repo, poz);
        if (existent == NULL) {
            distruge_medicament(m);
            return SERVICE_MEMORY_ERROR;
        }

        if (strcmp(get_nume(existent), nume) != 0 ||
            get_concentratie(existent) != concentratie) {
            distruge_medicament(m);
            return SERVICE_CONFLICT_ERROR;
        }

        if (!saveUndo(s)) {
            distruge_medicament(m);
            return SERVICE_MEMORY_ERROR;
        }

        Medicament* actualizat = creeaza_medicament(
            get_cod(existent),
            get_nume(existent),
            get_concentratie(existent),
            get_cantitate(existent) + cantitate
        );
        if (actualizat == NULL) {
            distruge_medicament(m);
            return SERVICE_MEMORY_ERROR;
        }

        if (!repoUpdateMedicament(&s->repo, actualizat)) {
            distruge_medicament(actualizat);
            distruge_medicament(m);
            return SERVICE_MEMORY_ERROR;
        }

        distruge_medicament(actualizat);
        distruge_medicament(m);
        return SERVICE_ADD_UPDATED;
    }

    if (!saveUndo(s)) {
        distruge_medicament(m);
        return SERVICE_MEMORY_ERROR;
    }

    if (!repoAddMedicament(&s->repo, m)) {
        distruge_medicament(m);
        return SERVICE_MEMORY_ERROR;
    }

    distruge_medicament(m);
    return SERVICE_ADD_CREATED;
}

int serviceUpdateMedicament(Service* s, int cod, const char* numeNou, float concentratieNoua) {
    if (s == NULL || numeNou == NULL) {
        return SERVICE_NULL_ERROR;
    }

    int poz = repoFindPositionByCod(&s->repo, cod);
    if (poz == -1) {
        return SERVICE_NOT_FOUND_ERROR;
    }

    Medicament* existent = repoGetMedicament(&s->repo, poz);
    if (existent == NULL) {
        return SERVICE_MEMORY_ERROR;
    }

    Medicament* actualizat = creeaza_medicament(
        cod,
        numeNou,
        concentratieNoua,
        get_cantitate(existent)
    );
    if (actualizat == NULL) {
        return SERVICE_MEMORY_ERROR;
    }

    if (valideaza_medicament(actualizat) != 0) {
        distruge_medicament(actualizat);
        return SERVICE_VALIDATION_ERROR;
    }

    if (!saveUndo(s)) {
        distruge_medicament(actualizat);
        return SERVICE_MEMORY_ERROR;
    }

    if (!repoUpdateMedicament(&s->repo, actualizat)) {
        distruge_medicament(actualizat);
        return SERVICE_MEMORY_ERROR;
    }

    distruge_medicament(actualizat);
    return SERVICE_SUCCESS;
}

int serviceDeleteMedicament(Service* s, int cod) {
    if (s == NULL) {
        return SERVICE_NULL_ERROR;
    }

    if (repoFindPositionByCod(&s->repo, cod) == -1) {
        return SERVICE_NOT_FOUND_ERROR;
    }

    if (!saveUndo(s)) {
        return SERVICE_MEMORY_ERROR;
    }

    if (!repoDeleteMedicament(&s->repo, cod)) {
        return SERVICE_MEMORY_ERROR;
    }

    return SERVICE_SUCCESS;
}

int serviceUndo(Service* s) {
    if (s == NULL) {
        return SERVICE_NULL_ERROR;
    }

    if (s->undoList.size == 0) {
        return SERVICE_UNDO_EMPTY;
    }

    int lastPos = s->undoList.size - 1;
    Repository* ultimaStare = (Repository*)s->undoList.elems[lastPos];

    destroyRepository(&s->repo);
    s->repo = *ultimaStare;

    free(ultimaStare);
    s->undoList.elems[lastPos] = NULL;
    s->undoList.size--;

    return SERVICE_SUCCESS;
}

List* serviceGetAll(Service* s) {
    if (s == NULL) {
        return NULL;
    }

    return repoGetAll(&s->repo);
}

int serviceSize(const Service* s) {
    if (s == NULL) {
        return 0;
    }

    return repoSize(&s->repo);
}

int comparaNume(const Medicament* m1, const Medicament* m2, int sens) {
    int rez = strcmp(get_nume(m1), get_nume(m2));

    if (sens == 1) {
        return rez > 0;
    }
    return rez < 0;
}

int comparaCantitate(const Medicament* m1, const Medicament* m2, int sens) {
    if (sens == 1) {
        return get_cantitate(m1) > get_cantitate(m2);
    }
    return get_cantitate(m1) < get_cantitate(m2);
}

int serviceSortGeneral(const Service* s, List* listaSortata, FunctieComparare functieComp, int sens) {
    if (s == NULL || listaSortata == NULL || functieComp == NULL) {
        return SERVICE_NULL_ERROR;
    }

    *listaSortata = copyList(repoGetAll((Repository*)&s->repo));
    if (listaSortata->elems == NULL && repoGetAll((Repository*)&s->repo)->elems != NULL) {
        return SERVICE_MEMORY_ERROR;
    }

    for (int i = 0; i < listaSortata->size - 1; i++) {
        for (int j = i + 1; j < listaSortata->size; j++) {
            Medicament* mi = (Medicament*)getElem(listaSortata, i);
            Medicament* mj = (Medicament*)getElem(listaSortata, j);

            if (functieComp(mi, mj, sens)) {
                void* temp = listaSortata->elems[i];
                listaSortata->elems[i] = listaSortata->elems[j];
                listaSortata->elems[j] = temp;
            }
        }
    }

    return SERVICE_SUCCESS;
}

int serviceFilterStockLessThan(const Service* s, List* listaFiltrata, int valoareLimita) {
    if (s == NULL || listaFiltrata == NULL) {
        return SERVICE_NULL_ERROR;
    }

    initResultList(listaFiltrata);
    if (listaFiltrata->elems == NULL) {
        return SERVICE_MEMORY_ERROR;
    }

    List* toate = repoGetAll((Repository*)&s->repo);
    for (int i = 0; i < sizeList(toate); i++) {
        Medicament* m = (Medicament*)getElem(toate, i);
        if (get_cantitate(m) < valoareLimita) {
            if (!addElem(listaFiltrata, m)) {
                destroyList(listaFiltrata);
                return SERVICE_MEMORY_ERROR;
            }
        }
    }

    return SERVICE_SUCCESS;
}

int serviceFilterNameStartsWith(const Service* s, List* listaFiltrata, char litera) {
    if (s == NULL || listaFiltrata == NULL) {
        return SERVICE_NULL_ERROR;
    }

    initResultList(listaFiltrata);
    if (listaFiltrata->elems == NULL) {
        return SERVICE_MEMORY_ERROR;
    }

    List* toate = repoGetAll((Repository*)&s->repo);
    for (int i = 0; i < sizeList(toate); i++) {
        Medicament* m = (Medicament*)getElem(toate, i);
        if (get_nume(m)[0] == litera) {
            if (!addElem(listaFiltrata, m)) {
                destroyList(listaFiltrata);
                return SERVICE_MEMORY_ERROR;
            }
        }
    }

    return SERVICE_SUCCESS;
}

int serviceFilterConcentrationGreaterThan(const Service* s, List* listaFiltrata, float valoareLimita) {
    if (s == NULL || listaFiltrata == NULL) {
        return SERVICE_NULL_ERROR;
    }

    initResultList(listaFiltrata);
    if (listaFiltrata->elems == NULL) {
        return SERVICE_MEMORY_ERROR;
    }

    List* toate = repoGetAll((Repository*)&s->repo);
    for (int i = 0; i < sizeList(toate); i++) {
        Medicament* m = (Medicament*)getElem(toate, i);
        if (get_concentratie(m) > valoareLimita) {
            if (!addElem(listaFiltrata, m)) {
                destroyList(listaFiltrata);
                return SERVICE_MEMORY_ERROR;
            }
        }
    }

    return SERVICE_SUCCESS;
}
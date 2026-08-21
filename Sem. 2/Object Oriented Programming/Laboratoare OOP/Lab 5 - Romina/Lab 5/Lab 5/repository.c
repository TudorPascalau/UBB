#include <stdio.h>
#include <stdlib.h>

#include "repository.h"

static int forceRepositoryAllocFail = 0;
static int forceRepoGetMedicamentFail = 0;
static int forceRepoDeleteFail = 0;

void setForceRepoDeleteFail(int value) {
    forceRepoDeleteFail = value;
}

void setForceRepoGetMedicamentFail(int value) {
    forceRepoGetMedicamentFail = value;
}

void setForceRepositoryAllocFail(int value) {
    forceRepositoryAllocFail = value;
}

Repository createRepository() {
    Repository repo;
    repo.medicamente = createList((CopyFunction)copiaza_medicament, (DestroyFunction)distruge_medicament);
    return repo;
}

void destroyRepository(Repository* repo) {
    //if (repo == NULL) {
    //    return;
    //}

    destroyList(&repo->medicamente);
}

int repoFindPositionByCod(const Repository* repo, int cod) {
    if (repo == NULL) {
        return -1;
    }

    for (int i = 0; i < repo->medicamente.size; i++) {
        Medicament* m = (Medicament*)getElem((List*)&repo->medicamente, i);
        if (m != NULL && get_cod(m) == cod) {
            return i;
        }
    }

    return -1;
}

int repoAddMedicament(Repository* repo, const Medicament* m) {
    if (repo == NULL || m == NULL) {
        return 0;
    }

    if (repoFindPositionByCod(repo, get_cod(m)) != -1) {
        return 0;
    }

    return addElem(&repo->medicamente, (void*)m);
}

int repoDeleteMedicament(Repository* repo, int cod) {
    if (repo == NULL) {
        return 0;
    }

    if (forceRepoDeleteFail) {
        return 0;
    }

    int pos = repoFindPositionByCod(repo, cod);
    if (pos == -1) {
        return 0;
    }

    return removeElem(&repo->medicamente, pos);
}

int repoUpdateMedicament(Repository* repo, const Medicament* mNou) {
    if (repo == NULL || mNou == NULL) {
        return 0;
    }

    int pos = repoFindPositionByCod(repo, get_cod(mNou));
    if (pos == -1) {
        return 0;
    }

    return setElem(&repo->medicamente, pos, (void*)mNou);
}

Medicament* repoGetMedicament(const Repository* repo, int pos) {
    if (repo == NULL) {
        return NULL;
    }

    if (forceRepoGetMedicamentFail) {
        return NULL;
    }

    return (Medicament*)getElem(&repo->medicamente, pos);
}

int repoSize(const Repository* repo) {
    if (repo == NULL) {
        return 0;
    }

    return sizeList((List*)&repo->medicamente);
}

List* repoGetAll(Repository* repo) {
    if (repo == NULL) {
        return NULL;
    }

    return &repo->medicamente;
}

Repository* copyRepository(const Repository* repo) {
    //if (repo == NULL) {
    //    return NULL;
    //}

    if (forceRepositoryAllocFail) {
        return NULL;
    }

    Repository* copie = (Repository*)malloc(sizeof(Repository));
    //if (copie == NULL) {
    //    return NULL;
    //}

    copie->medicamente = copyList(&repo->medicamente);

    if (repo->medicamente.elems != NULL && copie->medicamente.elems == NULL) {
        free(copie);
        return NULL;
    }

    return copie;
}

void destroyRepositoryPointer(void* repo) {
    if (repo == NULL) {
        return;
    }

    Repository* r = (Repository*)repo;
    destroyRepository(r);
    free(r);
}
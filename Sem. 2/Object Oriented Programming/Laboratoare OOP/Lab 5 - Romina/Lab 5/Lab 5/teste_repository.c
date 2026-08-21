#include "teste_repository.h"

#include <assert.h>
#include <string.h>
#include <stdio.h>

#include "repository.h"
#include "medicament.h"
#include "lista.h"

/*
* Testeaza crearea si distrugerea repository-ului.
*/
static void test_create_destroy_repository(void) {
    Repository repo = createRepository();

    assert(repoSize(&repo) == 0);
    assert(repoGetAll(&repo) != NULL);

    destroyRepository(&repo);

    assert(repoSize(&repo) == 0);
}

/*
* Testeaza adaugarea unui medicament.
*/
static void test_repo_add_medicament(void) {
    Repository repo = createRepository();

    Medicament* m = creeaza_medicament(1, "Paracetamol", 0.5f, 10);
    assert(m != NULL);

    assert(repoAddMedicament(&repo, m) == 1);
    assert(repoSize(&repo) == 1);

    Medicament* rez = repoGetMedicament(&repo, 0);
    assert(rez != NULL);
    assert(rez != m);
    assert(get_cod(rez) == 1);
    assert(strcmp(get_nume(rez), "Paracetamol") == 0);

    distruge_medicament(m);
    destroyRepository(&repo);
}

/*
* Testeaza adaugarea duplicata.
*/
static void test_repo_add_duplicate(void) {
    Repository repo = createRepository();

    Medicament* m1 = creeaza_medicament(1, "Paracetamol", 0.5f, 10);
    Medicament* m2 = creeaza_medicament(1, "Nurofen", 0.2f, 20);

    assert(m1 != NULL);
    assert(m2 != NULL);

    assert(repoAddMedicament(&repo, m1) == 1);
    assert(repoAddMedicament(&repo, m2) == 0);
    assert(repoSize(&repo) == 1);

    distruge_medicament(m1);
    distruge_medicament(m2);
    destroyRepository(&repo);
}

/*
* Testeaza cautarea dupa cod.
*/
static void test_repo_find_position(void) {
    Repository repo = createRepository();

    Medicament* m1 = creeaza_medicament(10, "A", 0.1f, 5);
    Medicament* m2 = creeaza_medicament(20, "B", 0.2f, 6);

    assert(repoAddMedicament(&repo, m1) == 1);
    assert(repoAddMedicament(&repo, m2) == 1);

    assert(repoFindPositionByCod(&repo, 10) == 0);
    assert(repoFindPositionByCod(&repo, 20) == 1);
    assert(repoFindPositionByCod(&repo, 99) == -1);

    distruge_medicament(m1);
    distruge_medicament(m2);
    destroyRepository(&repo);
}

/*
* Testeaza stergerea unui medicament.
*/
static void test_repo_delete_medicament(void) {
    Repository repo = createRepository();

    Medicament* m1 = creeaza_medicament(1, "A", 0.1f, 10);
    Medicament* m2 = creeaza_medicament(2, "B", 0.2f, 20);

    assert(repoAddMedicament(&repo, m1) == 1);
    assert(repoAddMedicament(&repo, m2) == 1);

    assert(repoDeleteMedicament(&repo, 1) == 1);
    assert(repoSize(&repo) == 1);

    Medicament* rez = repoGetMedicament(&repo, 0);
    assert(rez != NULL);
    assert(get_cod(rez) == 2);

    assert(repoDeleteMedicament(&repo, 100) == 0);

    distruge_medicament(m1);
    distruge_medicament(m2);
    destroyRepository(&repo);
}

/*
* Testeaza actualizarea unui medicament.
*/
static void test_repo_update_medicament(void) {
    Repository repo = createRepository();

    Medicament* m1 = creeaza_medicament(1, "A", 0.1f, 10);
    Medicament* mNou = creeaza_medicament(1, "A_modificat", 0.7f, 99);

    assert(repoAddMedicament(&repo, m1) == 1);
    assert(repoUpdateMedicament(&repo, mNou) == 1);

    Medicament* rez = repoGetMedicament(&repo, 0);
    assert(rez != NULL);
    assert(get_cod(rez) == 1);
    assert(strcmp(get_nume(rez), "A_modificat") == 0);
    assert(get_concentratie(rez) == 0.7f);
    assert(get_cantitate(rez) == 99);

    distruge_medicament(m1);
    distruge_medicament(mNou);
    destroyRepository(&repo);
}

/*
* Testeaza actualizarea unui medicament inexistent.
*/
static void test_repo_update_inexistent(void) {
    Repository repo = createRepository();

    Medicament* m = creeaza_medicament(5, "X", 0.5f, 50);
    assert(repoUpdateMedicament(&repo, m) == 0);

    distruge_medicament(m);
    destroyRepository(&repo);
}

/*
* Testeaza cazurile invalide.
*/
static void test_repo_invalid_cases(void) {
    assert(repoAddMedicament(NULL, NULL) == 0);
    assert(repoDeleteMedicament(NULL, 1) == 0);
    assert(repoUpdateMedicament(NULL, NULL) == 0);
    assert(repoFindPositionByCod(NULL, 1) == -1);
    assert(repoGetMedicament(NULL, 0) == NULL);
    assert(repoSize(NULL) == 0);
    assert(repoGetAll(NULL) == NULL);
}

/*
* Testeaza copierea profunda a unui repository.
*/
static void test_copy_repository_function() {
    Repository repo = createRepository();

    Medicament* m1 = creeaza_medicament(1, "Paracetamol", 500.0f, 10);
    Medicament* m2 = creeaza_medicament(2, "Nurofen", 200.0f, 20);

    assert(m1 != NULL);
    assert(m2 != NULL);

    assert(repoAddMedicament(&repo, m1) == 1);
    assert(repoAddMedicament(&repo, m2) == 1);

    Repository* copie = copyRepository(&repo);
    assert(copie != NULL);
    assert(repoSize(copie) == 2);

    Medicament* orig = repoGetMedicament(&repo, 0);
    Medicament* cp = repoGetMedicament(copie, 0);

    assert(orig != NULL);
    assert(cp != NULL);
    assert(orig != cp);
    assert(get_nume(orig) != get_nume(cp));
    assert(get_cod(orig) == get_cod(cp));
    assert(strcmp(get_nume(orig), get_nume(cp)) == 0);
    assert(get_concentratie(orig) == get_concentratie(cp));
    assert(get_cantitate(orig) == get_cantitate(cp));

    distruge_medicament(m1);
    distruge_medicament(m2);
    destroyRepository(&repo);
    destroyRepositoryPointer(copie);
}

/*
* Testeaza distrugerea unui repository alocat dinamic.
*/
static void test_destroy_repository_pointer_function() {
    Repository repo = createRepository();

    Medicament* m = creeaza_medicament(10, "Aulin", 100.0f, 5);
    assert(m != NULL);
    assert(repoAddMedicament(&repo, m) == 1);

    Repository* copie = copyRepository(&repo);
    assert(copie != NULL);

    destroyRepositoryPointer(copie);
    destroyRepositoryPointer(NULL);

    distruge_medicament(m);
    destroyRepository(&repo);
}

static void test_copy_repository_alloc_fail() {
    Repository repo = createRepository();
    Medicament* m = creeaza_medicament(1, "A", 1.0f, 1);

    assert(repoAddMedicament(&repo, m) == 1);

    setForceRepositoryAllocFail(1);
    Repository* copie = copyRepository(&repo);
    assert(copie == NULL);
    setForceRepositoryAllocFail(0);

    distruge_medicament(m);
    destroyRepository(&repo);
}

static void test_copy_repository_list_copy_fail() {
    Repository repo = createRepository();
    Medicament* m = creeaza_medicament(1, "A", 1.0f, 1);

    assert(repoAddMedicament(&repo, m) == 1);

    setForceListAllocFail(1);
    Repository* copie = copyRepository(&repo);
    assert(copie == NULL);
    setForceListAllocFail(0);

    distruge_medicament(m);
    destroyRepository(&repo);
}


/*
* Ruleaza toate testele pentru repository.
*/
void run_repository_tests() {
    test_create_destroy_repository();
    test_repo_add_medicament();
    test_repo_add_duplicate();
    test_repo_find_position();
    test_repo_delete_medicament();
    test_repo_update_medicament();
    test_repo_update_inexistent();
    test_repo_invalid_cases();
    test_copy_repository_function();
    test_destroy_repository_pointer_function();
    test_copy_repository_alloc_fail();
    test_copy_repository_list_copy_fail();


    printf("run_repository_tests() a rulat cu succes\n");
}
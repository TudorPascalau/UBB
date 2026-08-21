#include "teste_service.h"

#include <assert.h>
#include <string.h>
#include <stdio.h>

#include "service.h"
#include "medicament.h"
#include "lista.h"

static void test_service_add(void) {
    Service s = createService();

    int res1 = serviceAddMedicament(&s, 1, "Paracetamol", 500.0f, 10);
    assert(res1 == SERVICE_ADD_CREATED);
    assert(serviceSize(&s) == 1);

    int res2 = serviceAddMedicament(&s, 1, "Paracetamol", 500.0f, 5);
    assert(res2 == SERVICE_ADD_UPDATED);
    assert(serviceSize(&s) == 1);

    Medicament* m = (Medicament*)getElem(serviceGetAll(&s), 0);
    assert(get_cantitate(m) == 15);

    int res3 = serviceAddMedicament(&s, 2, "", 10.0f, 1);
    assert(res3 == SERVICE_VALIDATION_ERROR);

    int res4 = serviceAddMedicament(&s, 1, "AltNume", 700.0f, 3);
    assert(res4 == SERVICE_CONFLICT_ERROR);
    assert(serviceSize(&s) == 1);

    Medicament* m2 = (Medicament*)getElem(serviceGetAll(&s), 0);
    assert(strcmp(get_nume(m2), "Paracetamol") == 0);
    assert(get_concentratie(m2) == 500.0f);
    assert(get_cantitate(m2) == 15);

    destroyService(&s);
}

static void test_service_delete(void) {
    Service s = createService();

    serviceAddMedicament(&s, 1, "A", 10.0f, 5);
    serviceAddMedicament(&s, 2, "B", 20.0f, 6);

    assert(serviceDeleteMedicament(&s, 1) == SERVICE_SUCCESS);
    assert(serviceSize(&s) == 1);

    assert(serviceDeleteMedicament(&s, 100) == SERVICE_NOT_FOUND_ERROR);

    destroyService(&s);
}

static void test_service_update(void) {
    Service s = createService();

    serviceAddMedicament(&s, 1, "A", 10.0f, 5);

    assert(serviceUpdateMedicament(&s, 1, "A_mod", 20.0f) == SERVICE_SUCCESS);

    Medicament* m = (Medicament*)getElem(serviceGetAll(&s), 0);
    assert(strcmp(get_nume(m), "A_mod") == 0);
    assert(get_concentratie(m) == 20.0f);
    assert(get_cantitate(m) == 5); // cantitatea ramane

    assert(serviceUpdateMedicament(&s, 100, "X", 1.0f) == SERVICE_NOT_FOUND_ERROR);
    assert(serviceUpdateMedicament(&s, 1, "", 1.0f) == SERVICE_VALIDATION_ERROR);

    destroyService(&s);
}

static void test_service_sort(void) {
    Service s = createService();

    serviceAddMedicament(&s, 1, "B", 10.0f, 5);
    serviceAddMedicament(&s, 2, "A", 20.0f, 10);

    List sorted;

    assert(serviceSortGeneral(&s, &sorted, comparaNume, 1) == SERVICE_SUCCESS);

    Medicament* m0 = (Medicament*)getElem(&sorted, 0);
    Medicament* m1 = (Medicament*)getElem(&sorted, 1);

    assert(strcmp(get_nume(m0), "A") == 0);
    assert(strcmp(get_nume(m1), "B") == 0);

    destroyList(&sorted);
    destroyService(&s);
}

static void test_service_filter_stock(void) {
    Service s = createService();

    serviceAddMedicament(&s, 1, "A", 10.0f, 5);
    serviceAddMedicament(&s, 2, "B", 20.0f, 10);

    List filtered;

    assert(serviceFilterStockLessThan(&s, &filtered, 10) == SERVICE_SUCCESS);

    assert(sizeList(&filtered) == 1);
    Medicament* m = (Medicament*)getElem(&filtered, 0);
    assert(get_cod(m) == 1);

    destroyList(&filtered);
    destroyService(&s);
}

static void test_service_filter_name(void) {
    Service s = createService();

    serviceAddMedicament(&s, 1, "Paracetamol", 10.0f, 5);
    serviceAddMedicament(&s, 2, "Nurofen", 20.0f, 10);

    List filtered;

    assert(serviceFilterNameStartsWith(&s, &filtered, 'P') == SERVICE_SUCCESS);

    assert(sizeList(&filtered) == 1);
    Medicament* m = (Medicament*)getElem(&filtered, 0);
    assert(strcmp(get_nume(m), "Paracetamol") == 0);

    destroyList(&filtered);
    destroyService(&s);
}

static void test_service_filter_concentration(void) {
    Service s = createService();

    serviceAddMedicament(&s, 1, "A", 5.0f, 5);
    serviceAddMedicament(&s, 2, "B", 15.0f, 10);

    List filtered;

    assert(serviceFilterConcentrationGreaterThan(&s, &filtered, 10.0f) == SERVICE_SUCCESS);

    assert(sizeList(&filtered) == 1);
    Medicament* m = (Medicament*)getElem(&filtered, 0);
    assert(get_cod(m) == 2);

    destroyList(&filtered);
    destroyService(&s);
}

static void test_service_undo(void) {
    Service s = createService();

    assert(serviceUndo(&s) == SERVICE_UNDO_EMPTY);

    serviceAddMedicament(&s, 1, "A", 10.0f, 5);
    serviceAddMedicament(&s, 2, "B", 20.0f, 10);

    assert(serviceSize(&s) == 2);

    assert(serviceUndo(&s) == SERVICE_SUCCESS);
    assert(serviceSize(&s) == 1);

    serviceUpdateMedicament(&s, 1, "A_mod", 30.0f);
    Medicament* m = (Medicament*)getElem(serviceGetAll(&s), 0);
    assert(strcmp(get_nume(m), "A_mod") == 0);

    assert(serviceUndo(&s) == SERVICE_SUCCESS);
    m = (Medicament*)getElem(serviceGetAll(&s), 0);
    assert(strcmp(get_nume(m), "A") == 0);

    destroyService(&s);
}

static void test_compara_cantitate() {
    Medicament* m1 = creeaza_medicament(1, "A", 1.0f, 5);
    Medicament* m2 = creeaza_medicament(2, "B", 1.0f, 10);

    assert(comparaCantitate(m1, m2, 1) == 0);
    assert(comparaCantitate(m2, m1, 1) == 1);
    assert(comparaCantitate(m1, m2, 2) == 1);
    assert(comparaCantitate(m2, m1, 2) == 0);

    distruge_medicament(m1);
    distruge_medicament(m2);
}

static void test_service_null_cases_extra() {
    List l;

    assert(serviceAddMedicament(NULL, 1, "A", 1.0f, 1) == SERVICE_NULL_ERROR);
    assert(serviceUpdateMedicament(NULL, 1, "A", 1.0f) == SERVICE_NULL_ERROR);
    assert(serviceDeleteMedicament(NULL, 1) == SERVICE_NULL_ERROR);
    assert(serviceUndo(NULL) == SERVICE_NULL_ERROR);

    assert(serviceSortGeneral(NULL, &l, comparaNume, 1) == SERVICE_NULL_ERROR);
    assert(serviceSortGeneral(NULL, NULL, comparaNume, 1) == SERVICE_NULL_ERROR);

    assert(serviceFilterStockLessThan(NULL, &l, 10) == SERVICE_NULL_ERROR);
    assert(serviceFilterNameStartsWith(NULL, &l, 'A') == SERVICE_NULL_ERROR);
    assert(serviceFilterConcentrationGreaterThan(NULL, &l, 1.0f) == SERVICE_NULL_ERROR);
}

static void test_service_add_memory_errors() {
    Service s = createService();

    setForceMedicamentAllocFail(1);
    assert(serviceAddMedicament(&s, 1, "A", 1.0f, 1) == SERVICE_MEMORY_ERROR);
    setForceMedicamentAllocFail(0);

    setForceRepositoryAllocFail(1);
    assert(serviceAddMedicament(&s, 1, "A", 1.0f, 1) == SERVICE_MEMORY_ERROR);
    setForceRepositoryAllocFail(0);

    destroyService(&s);
}

static void test_service_add_conflict() {
    Service s = createService();

    assert(serviceAddMedicament(&s, 1, "Paracetamol", 500.0f, 10) == SERVICE_ADD_CREATED);
    assert(serviceAddMedicament(&s, 1, "AltNume", 500.0f, 5) == SERVICE_CONFLICT_ERROR);
    assert(serviceAddMedicament(&s, 1, "Paracetamol", 300.0f, 5) == SERVICE_CONFLICT_ERROR);

    destroyService(&s);
}

static void test_service_update_memory_errors() {
    Service s = createService();

    assert(serviceAddMedicament(&s, 1, "A", 1.0f, 1) == SERVICE_ADD_CREATED);

    setForceMedicamentAllocFail(1);
    assert(serviceUpdateMedicament(&s, 1, "B", 2.0f) == SERVICE_MEMORY_ERROR);
    setForceMedicamentAllocFail(0);

    setForceRepositoryAllocFail(1);
    assert(serviceUpdateMedicament(&s, 1, "B", 2.0f) == SERVICE_MEMORY_ERROR);
    setForceRepositoryAllocFail(0);

    destroyService(&s);
}

static void test_service_delete_memory_error() {
    Service s = createService();

    assert(serviceAddMedicament(&s, 1, "A", 1.0f, 1) == SERVICE_ADD_CREATED);

    setForceRepositoryAllocFail(1);
    assert(serviceDeleteMedicament(&s, 1) == SERVICE_MEMORY_ERROR);
    setForceRepositoryAllocFail(0);

    destroyService(&s);
}

static void test_destroy_service_null() {
    destroyService(NULL);
}

static void test_service_add_save_undo_fail() {
    Service s = createService();

    setForceRepositoryAllocFail(1);
    assert(serviceAddMedicament(&s, 1, "A", 1.0f, 1) == SERVICE_MEMORY_ERROR);
    setForceRepositoryAllocFail(0);

    destroyService(&s);
}

static void test_service_add_existing_repo_get_fail() {
    Service s = createService();
    assert(serviceAddMedicament(&s, 1, "A", 1.0f, 1) == SERVICE_ADD_CREATED);

    setForceRepoGetMedicamentFail(1);
    assert(serviceAddMedicament(&s, 1, "A", 1.0f, 1) == SERVICE_MEMORY_ERROR);
    setForceRepoGetMedicamentFail(0);

    destroyService(&s);
}

static void test_service_update_repo_get_fail() {
    Service s = createService();
    assert(serviceAddMedicament(&s, 1, "A", 1.0f, 1) == SERVICE_ADD_CREATED);

    setForceRepoGetMedicamentFail(1);
    assert(serviceUpdateMedicament(&s, 1, "B", 2.0f) == SERVICE_MEMORY_ERROR);
    setForceRepoGetMedicamentFail(0);

    destroyService(&s);
}

static void test_service_sort_copy_list_fail() {
    Service s = createService();
    List l;

    assert(serviceAddMedicament(&s, 1, "A", 1.0f, 1) == SERVICE_ADD_CREATED);

    setForceCopyListFail(1);
    assert(serviceSortGeneral(&s, &l, comparaNume, 1) == SERVICE_MEMORY_ERROR);
    setForceCopyListFail(0);

    destroyService(&s);
}

static void test_service_filter_create_list_fail() {
    Service s = createService();
    List l;

    setForceListAllocFail(1);
    assert(serviceFilterStockLessThan(&s, &l, 10) == SERVICE_MEMORY_ERROR);
    assert(serviceFilterNameStartsWith(&s, &l, 'A') == SERVICE_MEMORY_ERROR);
    assert(serviceFilterConcentrationGreaterThan(&s, &l, 1.0f) == SERVICE_MEMORY_ERROR);
    setForceListAllocFail(0);

    destroyService(&s);
}

static void test_service_filter_add_elem_fail() {
    Service s = createService();
    List l;

    assert(serviceAddMedicament(&s, 1, "A", 5.0f, 5) == SERVICE_ADD_CREATED);

    setForceAddElemFail(1);
    assert(serviceFilterStockLessThan(&s, &l, 10) == SERVICE_MEMORY_ERROR);
    setForceAddElemFail(0);

    setForceAddElemFail(1);
    assert(serviceFilterNameStartsWith(&s, &l, 'A') == SERVICE_MEMORY_ERROR);
    setForceAddElemFail(0);

    setForceAddElemFail(1);
    assert(serviceFilterConcentrationGreaterThan(&s, &l, 1.0f) == SERVICE_MEMORY_ERROR);
    setForceAddElemFail(0);

    destroyService(&s);
}

static void test_service_delete_repo_delete_fail() {
    Service s = createService();

    assert(serviceAddMedicament(&s, 1, "A", 1.0f, 1) == SERVICE_ADD_CREATED);

    setForceRepoDeleteFail(1);
    assert(serviceDeleteMedicament(&s, 1) == SERVICE_MEMORY_ERROR);
    setForceRepoDeleteFail(0);

    destroyService(&s);
}

void run_service_tests() {
    test_service_add();
    test_service_delete();
    test_service_update();
    test_service_sort();
    test_service_filter_stock();
    test_service_filter_name();
    test_service_filter_concentration();
    test_service_undo();
    test_compara_cantitate();
    test_service_null_cases_extra();
    test_service_add_memory_errors();
    test_service_add_conflict();
    test_service_update_memory_errors();
    test_service_delete_memory_error();
    test_destroy_service_null();
    test_service_add_save_undo_fail();
    test_service_add_existing_repo_get_fail();
    test_service_update_repo_get_fail();
    test_service_sort_copy_list_fail();
    test_service_filter_create_list_fail();
    test_service_filter_add_elem_fail();
    test_service_delete_repo_delete_fail();

    printf("run_service_tests() a rulat cu succes\n");
}

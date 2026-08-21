#include "teste_lista.h"

#include <assert.h>
#include <string.h>
#include <stdio.h>

#include "medicament.h"
#include "lista.h"

/*
* Testeaza crearea si distrugerea unei liste.
*/
static void test_create_destroy_list() {
    List l = createList((CopyFunction)copiaza_medicament, (DestroyFunction)distruge_medicament);

    assert(l.size == 0);
    assert(l.capacity >= 2);
    assert(l.elems != NULL);
    assert(l.copyElem != NULL);
    assert(l.destroyElem != NULL);

    destroyList(&l);

    assert(l.elems == NULL);
    assert(l.size == 0);
    assert(l.capacity == 0);
    assert(l.copyElem == NULL);
    assert(l.destroyElem == NULL);
}

/*
* Testeaza adaugarea si accesarea unui element.
*/
static void test_add_get_elem() {
    List l = createList((CopyFunction)copiaza_medicament, (DestroyFunction)distruge_medicament);

    Medicament* m = creeaza_medicament(1, "Paracetamol", 0.5f, 10);
    assert(m != NULL);

    assert(addElem(&l, m) == 1);
    assert(sizeList(&l) == 1);

    Medicament* dinLista = (Medicament*)getElem(&l, 0);
    assert(dinLista != NULL);
    assert(dinLista != m);
    assert(get_cod(dinLista) == 1);
    assert(strcmp(get_nume(dinLista), "Paracetamol") == 0);
    assert(get_concentratie(dinLista) == 0.5f);
    assert(get_cantitate(dinLista) == 10);

    distruge_medicament(m);
    destroyList(&l);
}

/*
* Testeaza redimensionarea listei.
*/
static void test_resize_list() {
    List l = createList((CopyFunction)copiaza_medicament, (DestroyFunction)distruge_medicament);

    for (int i = 0; i < 10; i++) {
        Medicament* m = creeaza_medicament(i + 1, "Test", 0.1f, i + 10);
        assert(m != NULL);
        assert(addElem(&l, m) == 1);
        distruge_medicament(m);
    }

    assert(sizeList(&l) == 10);
    assert(l.capacity >= 10);

    for (int i = 0; i < 10; i++) {
        Medicament* m = (Medicament*)getElem(&l, i);
        assert(m != NULL);
        assert(get_cod(m) == i + 1);
    }

    destroyList(&l);
}

/*
* Testeaza inlocuirea unui element din lista.
*/
static void test_set_elem() {
    List l = createList((CopyFunction)copiaza_medicament, (DestroyFunction)distruge_medicament);

    Medicament* m1 = creeaza_medicament(1, "A", 0.1f, 10);
    Medicament* m2 = creeaza_medicament(2, "B", 0.2f, 20);

    assert(m1 != NULL);
    assert(m2 != NULL);

    assert(addElem(&l, m1) == 1);
    assert(setElem(&l, 0, m2) == 1);

    Medicament* rez = (Medicament*)getElem(&l, 0);
    assert(rez != NULL);
    assert(get_cod(rez) == 2);
    assert(strcmp(get_nume(rez), "B") == 0);
    assert(get_concentratie(rez) == 0.2f);
    assert(get_cantitate(rez) == 20);

    distruge_medicament(m1);
    distruge_medicament(m2);
    destroyList(&l);
}

/*
* Testeaza stergerea unui element din lista.
*/
static void test_remove_elem() {
    List l = createList((CopyFunction)copiaza_medicament, (DestroyFunction)distruge_medicament);

    Medicament* m1 = creeaza_medicament(1, "A", 0.1f, 10);
    Medicament* m2 = creeaza_medicament(2, "B", 0.2f, 20);

    assert(m1 != NULL);
    assert(m2 != NULL);

    assert(addElem(&l, m1) == 1);
    assert(addElem(&l, m2) == 1);

    assert(removeElem(&l, 0) == 1);
    assert(sizeList(&l) == 1);

    Medicament* rez = (Medicament*)getElem(&l, 0);
    assert(rez != NULL);
    assert(get_cod(rez) == 2);
    assert(strcmp(get_nume(rez), "B") == 0);

    distruge_medicament(m1);
    distruge_medicament(m2);
    destroyList(&l);
}

/*
* Testeaza copierea profunda a unei liste.
*/
static void test_copy_list() {
    List l = createList((CopyFunction)copiaza_medicament, (DestroyFunction)distruge_medicament);

    Medicament* m1 = creeaza_medicament(1, "A", 0.1f, 10);
    Medicament* m2 = creeaza_medicament(2, "B", 0.2f, 20);

    assert(m1 != NULL);
    assert(m2 != NULL);

    assert(addElem(&l, m1) == 1);
    assert(addElem(&l, m2) == 1);

    List copie = copyList(&l);

    assert(copie.size == 2);

    Medicament* orig = (Medicament*)getElem(&l, 0);
    Medicament* cp = (Medicament*)getElem(&copie, 0);

    assert(orig != NULL);
    assert(cp != NULL);
    assert(cp != orig);
    assert(get_nume(cp) != get_nume(orig));
    assert(get_cod(cp) == get_cod(orig));
    assert(strcmp(get_nume(cp), get_nume(orig)) == 0);

    distruge_medicament(m1);
    distruge_medicament(m2);
    destroyList(&l);
    destroyList(&copie);
}

/*
* Testeaza cazurile invalide pentru lista.
*/
static void test_list_invalid_cases() {
    List l = createList((CopyFunction)copiaza_medicament, (DestroyFunction)distruge_medicament);

    assert(getElem(&l, -1) == NULL);
    assert(getElem(&l, 0) == NULL);
    assert(removeElem(&l, 0) == 0);
    assert(setElem(&l, 0, NULL) == 0);
    assert(addElem(&l, NULL) == 0);
    assert(sizeList(NULL) == 0);

    destroyList(&l);
}

static void test_create_list_alloc_fail() {
    setForceListAllocFail(1);

    List l = createList((CopyFunction)copiaza_medicament, (DestroyFunction)distruge_medicament);
    assert(l.elems == NULL);
    assert(l.capacity == 0);

    setForceListAllocFail(0);
}

static void test_resize_list_alloc_fail() {
    List l = createList((CopyFunction)copiaza_medicament, (DestroyFunction)distruge_medicament);

    Medicament* m1 = creeaza_medicament(1, "A", 1.0f, 1);
    Medicament* m2 = creeaza_medicament(2, "B", 1.0f, 1);
    Medicament* m3 = creeaza_medicament(3, "C", 1.0f, 1);

    assert(addElem(&l, m1) == 1);
    assert(addElem(&l, m2) == 1);

    setForceResizeAllocFail(1);
    assert(addElem(&l, m3) == 0);
    setForceResizeAllocFail(0);

    distruge_medicament(m1);
    distruge_medicament(m2);
    distruge_medicament(m3);
    destroyList(&l);
}

static void test_copy_list_null() {
    List l = copyList(NULL);
    assert(l.elems == NULL);
    assert(l.capacity == 0);
}

static void test_add_elem_copy_fail() {
    List l = createList((CopyFunction)copiaza_medicament, (DestroyFunction)distruge_medicament);
    Medicament* m = creeaza_medicament(1, "A", 1.0f, 1);

    setForceMedicamentAllocFail(1);
    assert(addElem(&l, m) == 0);
    setForceMedicamentAllocFail(0);

    distruge_medicament(m);
    destroyList(&l);
}

static void test_set_elem_copy_fail() {
    List l = createList((CopyFunction)copiaza_medicament, (DestroyFunction)distruge_medicament);

    Medicament* m1 = creeaza_medicament(1, "A", 1.0f, 1);
    Medicament* m2 = creeaza_medicament(2, "B", 2.0f, 2);

    assert(addElem(&l, m1) == 1);

    setForceMedicamentAllocFail(1);
    assert(setElem(&l, 0, m2) == 0);
    setForceMedicamentAllocFail(0);

    distruge_medicament(m1);
    distruge_medicament(m2);
    destroyList(&l);
}

static void test_copy_list_add_elem_fail() {
    List l = createList((CopyFunction)copiaza_medicament, (DestroyFunction)distruge_medicament);

    Medicament* m = creeaza_medicament(1, "Paracetamol", 10.0f, 20);
    assert(m != NULL);
    assert(addElem(&l, m) == 1);
    distruge_medicament(m);

    setForceAddElemFail(1);
    List copie = copyList(&l);
    setForceAddElemFail(0);

    assert(copie.elems == NULL);
    assert(copie.size == 0);
    assert(copie.capacity == 0);
    assert(copie.copyElem == l.copyElem);
    assert(copie.destroyElem == l.destroyElem);

    destroyList(&l);
}

/*
* Ruleaza toate testele pentru lista.
*/
void run_list_tests() {
    test_create_destroy_list();
    test_add_get_elem();
    test_resize_list();
    test_set_elem();
    test_remove_elem();
    test_copy_list();
    test_list_invalid_cases();
    test_create_list_alloc_fail();
    test_resize_list_alloc_fail();
    test_copy_list_null();
    test_add_elem_copy_fail();
    test_set_elem_copy_fail();
    test_copy_list_add_elem_fail();

    printf("run_list_tests() a rulat cu succes\n");
}
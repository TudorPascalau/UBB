#include "teste_validare.h"

#include <assert.h>
#include <stdio.h>

#include "medicament.h"
#include "validare.h"

static void test_valideaza_medicament_valid(void) {
    Medicament* m = creeaza_medicament(1, "Paracetamol", 500.0f, 10);
    assert(m != NULL);

    assert(valideaza_medicament(m) == 0);

    distruge_medicament(m);
}

static void test_valideaza_medicament_null(void) {
    assert(valideaza_medicament(NULL) == 1);
}

static void test_valideaza_medicament_cod_invalid(void) {
    Medicament* m = creeaza_medicament(0, "Paracetamol", 500.0f, 10);
    assert(m != NULL);

    assert(valideaza_medicament(m) == 2);

    distruge_medicament(m);
}

static void test_valideaza_medicament_nume_invalid(void) {
    Medicament* m = creeaza_medicament(1, "", 500.0f, 10);
    assert(m != NULL);

    assert(valideaza_medicament(m) == 3);

    distruge_medicament(m);
}

static void test_valideaza_medicament_concentratie_invalida(void) {
    Medicament* m = creeaza_medicament(1, "Paracetamol", 0.0f, 10);
    assert(m != NULL);

    assert(valideaza_medicament(m) == 4);

    distruge_medicament(m);
}

static void test_valideaza_medicament_cantitate_invalida(void) {
    Medicament* m = creeaza_medicament(1, "Paracetamol", 500.0f, 0);
    assert(m != NULL);

    assert(valideaza_medicament(m) == 5);

    distruge_medicament(m);
}

void run_validare_tests(void) {
    test_valideaza_medicament_valid();
    test_valideaza_medicament_null();
    test_valideaza_medicament_cod_invalid();
    test_valideaza_medicament_nume_invalid();
    test_valideaza_medicament_concentratie_invalida();
    test_valideaza_medicament_cantitate_invalida();

    printf("run_validare_tests() a rulat cu succes\n");
}
#include <assert.h>
#include <string.h>
#include <stdio.h>
#include "medicament.h"

/*
* Testeaza crearea unui medicament valid.
*/
static void test_creeaza_medicament() {
	Medicament* m = creeaza_medicament(1, "Paracetamol", 0.5f, 10);

	assert(m != NULL);
	assert(get_cod(m) == 1);
	assert(strcmp(get_nume(m), "Paracetamol") == 0);
	assert(get_concentratie(m) == 0.5f);
	assert(get_cantitate(m) == 10);

	distruge_medicament(m);
}

/*
* Testeaza crearea unui medicament cu nume NULL.
*/
static void test_creeaza_medicament_nume_null() {
	Medicament* m = creeaza_medicament(1, NULL, 0.5f, 10);
	assert(m == NULL);
}

/*
* Testeaza copierea profunda a unui medicament.
*/
static void test_copiaza_medicament() {
	Medicament* m1 = creeaza_medicament(2, "Nurofen", 0.4f, 20);
	assert(m1 != NULL);

	Medicament* m2 = copiaza_medicament(m1);
	assert(m2 != NULL);

	assert(m2 != m1);
	assert(get_cod(m2) == get_cod(m1));
	assert(strcmp(get_nume(m2), get_nume(m1)) == 0);
	assert(get_concentratie(m2) == get_concentratie(m1));
	assert(get_cantitate(m2) == get_cantitate(m1));

	/* verificare deep copy */
	assert(get_nume(m2) != get_nume(m1));

	distruge_medicament(m1);
	distruge_medicament(m2);
}

/*
* Testeaza copierea unui pointer NULL.
*/
static void test_copiaza_medicament_null() {
	Medicament* copie = copiaza_medicament(NULL);
	assert(copie == NULL);
}

/*
* Functii de coverage erori memorie
*/
static void test_creeaza_medicament_alloc_fail() {
	setForceMedicamentAllocFail(1);
	Medicament* m = creeaza_medicament(1, "A", 1.0f, 1);
	assert(m == NULL);
	setForceMedicamentAllocFail(0);
}

static void test_creeaza_medicament_nume_alloc_fail() {
	setForceNumeAllocFail(1);
	Medicament* m = creeaza_medicament(1, "A", 1.0f, 1);
	assert(m == NULL);
	setForceNumeAllocFail(0);
}

static void test_create_medicament_null_name() {
	Medicament* m = creeaza_medicament(1, NULL, 10.5f, 20);
	assert(m == NULL);
}

void run_domain_tests() {
	test_creeaza_medicament();
	test_creeaza_medicament_nume_null();
	test_copiaza_medicament();
	test_copiaza_medicament_null();
	test_creeaza_medicament_alloc_fail();
	test_creeaza_medicament_nume_alloc_fail();
	test_create_medicament_null_name();

	printf("run_domain_tests() a rulat cu succes\n");
}
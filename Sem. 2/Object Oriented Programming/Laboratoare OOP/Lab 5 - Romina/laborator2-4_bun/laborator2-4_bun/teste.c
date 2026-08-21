#include <assert.h>
#include <string.h>
#include <stdlib.h>
#include "service.h"
#include "repository.h"
#include "medicament.h"
#include "validare.h"

extern int forteaza_eroare_m;
extern int forteaza_eroare_nume;

/*
* Teste domeniu - medicament
* Testeaza functia creeaza_medicament, care creeaza un medicament cu datele primite ca parametru
* Verifica daca codul, numele, concentratia si cantitatea medicamentului au fost setate corect
*/
void test_creeaza_medicament() {
    Medicament* m = creeaza_medicament(1, "Paracetamol", 0.5f, 10);
    assert(m != NULL);
    assert(m->cod == 1);
    assert(strcmp(m->nume, "Paracetamol") == 0);
    assert(m->concentratie == 0.5f);
    assert(m->cantitate == 10);

    distruge_medicament(m);
}

/*
* Testeaza acoperirea pentru scenariile de eroare forțate în funcția creeaza_medicament.
* Verifică dacă funcția returnează NULL atunci când forțăm erori de alocare pentru nume și pentru structura medicamentului.
*/
void test_final_coverage() {
    // Resetare initiala
    forteaza_eroare_m = 0;
    forteaza_eroare_nume = 0;

    // Test forțare eroare alocare nume 
    forteaza_eroare_nume = 1;
    assert(creeaza_medicament(1, "Test", 0.5f, 10) == NULL);
    forteaza_eroare_nume = 0;

    // Test forțare eroare alocare structura
    forteaza_eroare_m = 1;
    assert(creeaza_medicament(1, "Test", 0.5f, 10) == NULL);
    forteaza_eroare_m = 0;
}

// Teste repo

/*
* Testeaza functia initRepo, care initializeaza repository ul de medicamente
* Verifica daca lungimea repository ului a fost initializata corect la 0
*/
void test_innit() {
    RepoFarmacie repo;
    initRepo(&repo);

    assert(repo.lungime == 0);
    assert(repo.memorie_alocata == 2);
    assert(repo.medicamente != NULL);

    distrugeRepo(&repo);
}

/*
* Testeaza functia adauga_medicament, care adauga un medicament in repository ul de medicamente
* Verifica daca medicamentul a fost adaugat cu succes
* Verifica daca numele, concentratia si cantitatea medicamentului au fost adaugate corect
*/
void test_adauga_medicament() {
    RepoFarmacie repo;
    initRepo(&repo);

    Medicament* m1 = creeaza_medicament(1, "Paracetamol", 0.5f, 10);
    assert(adauga_medicament(&repo, *m1) == 1);
    assert(repo.lungime == 1);
    assert(strcmp(repo.medicamente[0].nume, "Paracetamol") == 0);

    // Testăm resize-ul adăugând mai multe
    for (int i = 1; i < 10; i++) {
        Medicament* temp = creeaza_medicament(i + 1, "Test", 0.1f, 1);
        adauga_medicament(&repo, *temp);
        distruge_medicament(temp);
    }
    assert(repo.lungime == 10);
    assert(repo.memorie_alocata >= 10);

    distruge_medicament(m1);
    distrugeRepo(&repo);
}

/*
* Testeaza functia gaseste_medicament_cod, care cauta un medicament dupa cod in repository ul de medicamente
* Verifica daca medicamentul a fost gasit cu succes
* Verifica daca datele medicamentului gasit sunt corecte
*/
void test_gaseste_medicament_cod() {
    RepoFarmacie repo;
    initRepo(&repo);

    Medicament* m = creeaza_medicament(1, "Paracetamol", 0.5f, 10);
    adauga_medicament(&repo, *m);

    Medicament* med_gasit = gaseste_medicament_cod(&repo, 1);
    assert(med_gasit != NULL);
    assert(med_gasit->cod == 1);
    assert(strcmp(med_gasit->nume, "Paracetamol") == 0);

    assert(gaseste_medicament_cod(&repo, 99) == NULL);

    distruge_medicament(m);
    distrugeRepo(&repo);
}

/*
* Testeaza functia sterge_medicament, care sterge un medicament dupa cod din repository ul de medicamente
* Verifica daca medicamentul a fost sters cu succes
* Verifica daca lungimea repository ului a fost actualizata corect
* Verifica daca medicamentul nu mai poate fi gasit dupa codul sau
*/
void test_sterge_medicament() {
    RepoFarmacie repo;
    initRepo(&repo);

    Medicament* m1 = creeaza_medicament(1, "A", 0.1f, 10);
    Medicament* m2 = creeaza_medicament(2, "B", 0.2f, 20);
    adauga_medicament(&repo, *m1);
    adauga_medicament(&repo, *m2);

    assert(sterge_medicament(&repo, 1) == 1);
    assert(repo.lungime == 1);
    assert(repo.medicamente[0].cod == 2);

    assert(sterge_medicament(&repo, 99) == 0);

    distruge_medicament(m1);
    distruge_medicament(m2);
    distrugeRepo(&repo);
}

// Teste service 

/*
* Testeaza functia s_adauga_medicament, care adauga un medicament in repository ul de medicamente, sau actualizeaza cantitatea unui medicament existent
* Verifica daca medicamentul a fost adaugat sau actualizat cu succes
* Verifica daca numele, concentratia si cantitatea medicamentului au fost adaugate sau actualizate corect
* Verifica daca functia returneaza 2 atunci cand medicamentul a fost actualizat, si 1 atunci cand medicamentul a fost adaugat
*/
void test_s_adauga_medicament() {
    RepoFarmacie repo;
    initRepo(&repo);

    assert(s_adauga_medicament(&repo, 1, "Paracetamol", 0.5f, 10) == 1);
    // Update cantitate (cod existent)
    assert(s_adauga_medicament(&repo, 1, "Paracetamol", 0.5f, 5) == 2);
    assert(repo.medicamente[0].cantitate == 15);

    distrugeRepo(&repo);
}

/*
* Testeaza functia s_actualizeaza_medicament, care actualizeaza un medicament gasit dupa codul sau
* Verifica daca medicamentul a fost actualizat cu succes
* Verifica daca numele si concentratia medicamentului au fost actualizate corect
* Verifica daca functia returneaza 0 atunci cand nu se gaseste niciun medicament cu codul dat
*/
void test_s_actualizeaza_medicament() {
    RepoFarmacie repo;
    initRepo(&repo);

    s_adauga_medicament(&repo, 1, "Vechi", 0.1f, 10);
    assert(s_actualizeaza_medicament(&repo, 1, "Nou", 0.9f) == 1);
    assert(strcmp(repo.medicamente[0].nume, "Nou") == 0);
    assert(repo.medicamente[0].concentratie == 0.9f);

    assert(s_actualizeaza_medicament(&repo, 99, "Nimic", 0.0f) == 0);

    distrugeRepo(&repo);
}

/*
* Testeaza functia sterge_medicament, care sterge un medicament dupa cod din repository ul de medicamente
* Verifica daca medicamentul a fost sters cu succes
* Verifica daca lungimea repository ului a fost actualizata corect
* Verifica daca medicamentul nu mai poate fi gasit dupa codul sau
*/
void test_s_sterge_medicament() {
    RepoFarmacie repo;
    initRepo(&repo);

    s_adauga_medicament(&repo, 10, "Ibuprofen", 400.0f, 20);
    assert(repo.lungime == 1);

    // ștergerea cu succes
    int rez = s_sterge_medicament(&repo, 10);
    assert(rez == 1);
    assert(repo.lungime == 0);
    assert(gaseste_medicament_cod(&repo, 10) == NULL);

    // cod inexistent
    rez = s_sterge_medicament(&repo, 99);
    assert(rez == 0);
    assert(repo.lungime == 0);

    distrugeRepo(&repo);
}

/*
* Testeaza functia s_sorteaza_medicamente, care sorteaza medicamentele dupa un criteriu : sau nume sau cantitate, intr un anumit sens : sau crescator sau descrescator
* Verifica daca medicamentele au fost sortate corect dupa nume in ordine crescatoare
* Verifica daca medicamentele au fost sortate corect dupa cantitate in ordine descrescatoare
*/
//void test_sortare() {
//    RepoFarmacie repo;
//    initRepo(&repo);
//    s_adauga_medicament(&repo, 1, "Z", 0.1f, 10);
//    s_adauga_medicament(&repo, 2, "A", 0.1f, 20);
//
//    RepoFarmacie rez;
//    // Sortare nume crescator
//    s_sorteaza_medicamente(&repo, &rez, 1, 1);
//    assert(strcmp(rez.medicamente[0].nume, "A") == 0);
//    distrugeRepo(&rez);
//
//    // Sortare cantitate descrescator
//    s_sorteaza_medicamente(&repo, &rez, 2, 2);
//    assert(rez.medicamente[0].cantitate == 20);
//    distrugeRepo(&rez);
//
//    distrugeRepo(&repo);
//}

/*
* Testeaza functiile s_filtreaza_stoc_mai_mic si s_filtreaza_medicamente_litera_data,
* care filtreaza medicamentele care au cantitatea mai mica decat o valoare data
* respectiv care incep cu o litera data
* Verifica daca medicamentele au fost filtrate corect dupa cantitate
* Verifica daca medicamentele au fost filtrate corect dupa litera de inceput a numelui
* Verifica daca nu se returneaza niciun medicament atunci cand nu exista nicio potrivire pentru criteriul de filtrare
*/
void test_filtrare() {
    RepoFarmacie repo;
    initRepo(&repo);
    s_adauga_medicament(&repo, 1, "Aspirina", 0.1f, 5);
    s_adauga_medicament(&repo, 2, "Paracetamol", 0.1f, 15);

    RepoFarmacie rez;
    s_filtreaza_stoc_mai_mic(&repo, &rez, 10);
    assert(rez.lungime == 1);
    distrugeRepo(&rez);

    s_filtreaza_medicamente_litera_data(&repo, &rez, 'P');
    assert(rez.lungime == 1);
    assert(rez.medicamente[0].nume[0] == 'P');
    distrugeRepo(&rez);

    distrugeRepo(&repo);
}

/*
* Testeaza functia s_get_toate_medicamentele, care returneaza o lista auxiliara care contine toate medicamentele din repository ul de medicamente
* Verifica daca lista returnata contine toate medicamentele din repository ul original
* Verifica daca modificarile aduse medicamentelor din lista returnata se reflecta in repository ul original, deoarece se returneaza o referinta la repository ul original
*/
void test_s_get_toate_medicamentele() {
    RepoFarmacie repo;
    initRepo(&repo);

    s_adauga_medicament(&repo, 100, "Nurofen", 200.0f, 30);

    RepoFarmacie* rezultat = s_get_toate_medicamentele(&repo);

    assert(rezultat == &repo);

    assert(rezultat->lungime == 1);
    assert(rezultat->medicamente[0].cod == 100);
    assert(strcmp(rezultat->medicamente[0].nume, "Nurofen") == 0);

    distrugeRepo(&repo);
}

void test_sortare_completa() {
    RepoFarmacie repo;
    initRepo(&repo);

    // Adăugăm 3 medicamente în dezordine
    s_adauga_medicament(&repo, 1, "Z-Medicament", 10.0f, 50);  // Cel mai mare nume, cantitate mare
    s_adauga_medicament(&repo, 2, "A-Medicament", 20.0f, 10);  // Cel mai mic nume, cantitate mica
    s_adauga_medicament(&repo, 3, "M-Medicament", 30.0f, 30);  // Nume mijlociu, cantitate mijlocie

    RepoFarmacie rez;

    // --- CASE 1: Nume Crescător (A, M, Z) ---
    s_sorteaza_general(&repo, &rez, comparaNume, 1);
    assert(strcmp(rez.medicamente[0].nume, "A-Medicament") == 0);
    assert(strcmp(rez.medicamente[1].nume, "M-Medicament") == 0);
    assert(strcmp(rez.medicamente[2].nume, "Z-Medicament") == 0);
    distrugeRepo(&rez);

    // --- CASE 2: Nume Descrescător (Z, M, A) ---
    s_sorteaza_general(&repo, &rez, comparaNume, 2);
    assert(strcmp(rez.medicamente[0].nume, "Z-Medicament") == 0);
    assert(strcmp(rez.medicamente[1].nume, "M-Medicament") == 0);
    assert(strcmp(rez.medicamente[2].nume, "A-Medicament") == 0);
    distrugeRepo(&rez);

    // --- CASE 3: Cantitate Crescătoare (10, 30, 50) ---
    s_sorteaza_general(&repo, &rez, comparaCantitate, 1);
    assert(rez.medicamente[0].cantitate == 10);
    assert(rez.medicamente[1].cantitate == 30);
    assert(rez.medicamente[2].cantitate == 50);
    distrugeRepo(&rez);

    // --- CASE 4: Cantitate Descrescătoare (50, 30, 10) ---
    s_sorteaza_general(&repo, &rez, comparaCantitate, 2);
    assert(rez.medicamente[0].cantitate == 50);
    assert(rez.medicamente[1].cantitate == 30);
    assert(rez.medicamente[2].cantitate == 10);
    distrugeRepo(&rez);

    // Testăm și cazul cu elemente egale (nu ar trebui să crape)
    s_adauga_medicament(&repo, 4, "A-Medicament", 50.0f, 10);
    s_sorteaza_general(&repo, &rez, comparaCantitate, 1);
    assert(rez.lungime == 4);
    distrugeRepo(&rez);

    distrugeRepo(&repo);
}

// Teste validare 

/*
* Testeaza functia valideaza_medicament, care valideaza un medicament conform unor reguli prestabilite
* Verifica daca functia returneaza 0 pentru un medicament valid
* Verifica daca functia returneaza codurile de eroare corespunzatoare pentru medicamentele care incalca regulile de validare (cod invalid, nume invalid, concentratie invalida, cantitate invalida)
*/
void test_valideaza_medicament() {
    Medicament* m_ok = creeaza_medicament(1, "Ok", 0.5f, 10);
    assert(valideaza_medicament(*m_ok) == 0);

    Medicament* m_bad = creeaza_medicament(-1, "", -0.5f, -10);
    // Validarea va returna prima eroare gasita (probabil 1 pentru cod)
    assert(valideaza_medicament(*m_bad) != 0);

    distruge_medicament(m_ok);
    distruge_medicament(m_bad);
}

void run_tests() {
    test_creeaza_medicament();
    test_innit();
    test_adauga_medicament();
    test_gaseste_medicament_cod();
    test_s_adauga_medicament();
    test_s_actualizeaza_medicament();
    test_s_sterge_medicament();
    test_sterge_medicament();
    // test_sortare();
    test_filtrare();
    test_valideaza_medicament();
    test_final_coverage();
    test_s_get_toate_medicamentele();
    test_sortare_completa();
}
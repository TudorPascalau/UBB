#include <stdio.h>
#include "service.h"
#include "validare.h"
//
//
//void ui_afiseaza_stoc_actual(RepoFarmacie* repo) {
//    if (repo->lungime == 0) {
//        printf("Stocul farmaciei este gol.\n");
//        return;
//    }
//    for (int i = 0; i < repo->lungime; i++) {
//        Medicament m = repo->medicamente[i];
//        printf("Cod: %d, Nume: %s, Concentratie: %.2f, Cantitate: %d\n", m.cod, m.nume, m.concentratie, m.cantitate);
//    }
//}
//
//void ui_adauga(RepoFarmacie* repo) {
//    int cod, cantitate;
//    char nume[50];
//    float concentratie;
//    printf("Cod unic: "); scanf_s("%d", &cod);
//    printf("Nume medicament: "); scanf_s("%s", nume, 50);
//    printf("Concentratie: "); scanf_s("%f", &concentratie);
//    printf("Cantitate de adaugat: "); scanf_s("%d", &cantitate);
//
//    Medicament* m = creeaza_medicament(cod, nume, concentratie, cantitate);
//    if (m == NULL) { printf("Eroare alocare!\n"); return; }
//
//    int eroare = valideaza_medicament(*m);
//    if (eroare != 0) {
//        if (eroare == 1) printf("Codul medicamentului trebuie sa fie un numar pozitiv!\n");
//        else if (eroare == 2) printf("Numele medicamentului nu poate fi vid!\n");
//        else if (eroare == 3) printf("Concentratia medicamentului trebuie sa fie un numar pozitiv!\n");
//        else if (eroare == 4) printf("Cantitatea medicamentului trebuie sa fie un numar pozitiv!\n");
//        distruge_medicament(m);
//        return;
//    }
//    int rez = s_adauga_medicament(repo, cod, nume, concentratie, cantitate);
//    if (rez == 1) printf("Medicament adaugat cu succes.\n");
//    else if (rez == 2) printf("Medicament existent - cantitate actualizata.\n");
//    else printf("Eroare: Stocul farmaciei este plin!\n");
//    distruge_medicament(m);
//}
//
//void ui_actualizeaza(RepoFarmacie* repo) {
//    int cod; char nume_nou[50]; float concentratie_noua;
//    printf("Codul medicamentului de actualizat: "); scanf_s("%d", &cod);
//    printf("Nume nou: "); scanf_s("%s", nume_nou, 50);
//    printf("Concentratie noua: "); scanf_s("%f", &concentratie_noua);
//    if (s_actualizeaza_medicament(repo, cod, nume_nou, concentratie_noua) == 1) printf("Medicament actualizat cu succes.\n");
//    else printf("Eroare: Nu s-a gasit niciun medicament cu codul dat!\n");
//}
//
//void ui_sterge_medicament(RepoFarmacie* repo) {
//    int cod;
//    printf("Codul medicamentului de sters: "); scanf_s("%d", &cod);
//    if (s_sterge_medicament(repo, cod) == 1) printf("Medicament sters cu succes.\n");
//    else printf("Eroare: Nu s-a gasit niciun medicament cu codul dat!\n");
//}
//
//void ui_sortare_nume_cant_c_d(RepoFarmacie* repo) {
//    int criteriu, sens;
//    printf("Criteriu\n    1. Nume\n    2. Cantitate\n"); 
//    scanf_s("%d", &criteriu);
//    printf("Sens:\n    1. Crescator\n    2. Descrescator\n"); 
//    scanf_s("%d", &sens);
//
//    if ((criteriu == 1 || criteriu == 2) && (sens == 1 || sens == 2)) {
//        RepoFarmacie lista_sortata;
//        if (criteriu == 1) {
//            s_sorteaza_general(repo, &lista_sortata, comparaNume, sens);
//        }
//        else {
//            s_sorteaza_general(repo, &lista_sortata, comparaCantitate, sens);
//        }
//
//        ui_afiseaza_stoc_actual(&lista_sortata);
//        distrugeRepo(&lista_sortata);
//    }
//    else {
//        printf("Optiuni invalide!\n");
//    }
//}
//
//void ui_filtrare(RepoFarmacie* repo) {
//    int optiune;
//    printf("Doriti sa filtrati medicamentele care :\n    1. au cantitatea mai mica decat un numar dat\n    2. au denumirea ce incepe cu o anumita litera\n"); scanf_s("%d", &optiune);
//    RepoFarmacie lista_filtrata;
//    if (optiune == 1) {
//        int val; 
//        printf("Valoarea limita: "); 
//        scanf_s("%d", &val);
//        s_filtreaza_stoc_mai_mic(repo, &lista_filtrata, val);
//        ui_afiseaza_stoc_actual(&lista_filtrata);
//        distrugeRepo(&lista_filtrata);
//    }
//    else if (optiune == 2) {
//        char lit; printf("Litera: "); 
//        scanf_s(" %c", &lit, 1);
//        s_filtreaza_medicamente_litera_data(repo, &lista_filtrata, lit);
//        ui_afiseaza_stoc_actual(&lista_filtrata);
//        distrugeRepo(&lista_filtrata);
//    }
//    else printf("Optiune invalida!\n");
//}
//
//void run_ui() {
//    RepoFarmacie repo; initRepo(&repo);
//    while (1) {
//        printf("Alege comanda dorita:\n    1. Adauga/Actualizeaza medicament\n    2. Actualizare nume si concentatie\n    3. Sterge stoc dupa cod\n    4. Ordoneaza stoc\n    5. Filtreaza stoc\n    0. Iesire\nComanda: ");
//        int cmd; if (scanf_s("%d", &cmd) != 1) { 
//            while (getchar() != '\n'); 
//            continue; }
//        if (cmd == 1) { 
//            ui_adauga(&repo); 
//            printf("Stocul actual:\n"); 
//            ui_afiseaza_stoc_actual(&repo); 
//        }
//        else if (cmd == 2) { 
//            ui_actualizeaza(&repo); 
//            printf("Stocul actual:\n"); 
//            ui_afiseaza_stoc_actual(&repo); 
//        }
//        else if (cmd == 3) { 
//            ui_sterge_medicament(&repo); 
//            printf("Stocul actual:\n"); 
//            ui_afiseaza_stoc_actual(&repo); 
//        }
//        else if (cmd == 4) 
//            ui_sortare_nume_cant_c_d(&repo);
//        else if (cmd == 5) 
//            ui_filtrare(&repo);
//        else if (cmd == 0) 
//            break;
//        else printf("Comanda invalida!\n");
//    }
//    distrugeRepo(&repo);
//}
#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <stdio.h>
#include <crtdbg.h>
#include "teste.h"
#include "ui.h"

extern int forteaza_eroare_m;
extern int forteaza_eroare_nume;

int main() {
    run_tests();

    //forteaza_eroare_m = 0;
    //forteaza_eroare_nume = 0;

    //printf("Toate testele au trecut cu succes!\n");

    //if (_CrtDumpMemoryLeaks() == 1) {
    //    printf("Au fost detectate scurgeri de memorie!\n");
    //}
    //else
    //    printf("Nu au fost detectate scurgeri de memorie!\n");

    //run_ui();

    return 0;
}
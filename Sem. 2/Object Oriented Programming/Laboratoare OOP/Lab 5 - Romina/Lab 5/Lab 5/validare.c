#include "validare.h"

#include <string.h>

int valideaza_medicament(const Medicament* m) {
    if (m == NULL) {
        return 1;
    }

    if (m->cod <= 0) {
        return 2;
    }

    if (m->nume == NULL || strlen(m->nume) == 0) {
        return 3;
    }

    if (m->concentratie <= 0) {
        return 4;
    }

    if (m->cantitate <= 0) {
        return 5;
    }

    return 0;
}
#include "validare.h"
#include <string.h>

int valideaza_medicament(Medicament m) {
    if (m.cod <= 0) return 1;
    if (strlen(m.nume) == 0) return 2;
    if (m.concentratie <= 0) return 3;
    if (m.cantitate <= 0) return 4;
    return 0;
}

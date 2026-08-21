#include "ui.h"

#include <stdio.h>

static void clearInputBuffer(void) {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

static int readInt(int* x) {
    if (scanf_s("%d", x) != 1) {
        printf("Input invalid.\n");
        clearInputBuffer();
        return 0;
    }
    return 1;
}

static int readFloat(float* x) {
    if (scanf_s("%f", x) != 1) {
        printf("Input invalid.\n");
        clearInputBuffer();
        return 0;
    }
    return 1;
}

static int readString(char* s, int maxLen) {
    if (scanf_s("%s", s, (unsigned)maxLen) != 1) {
        printf("Input invalid.\n");
        clearInputBuffer();
        return 0;
    }
    return 1;
}

static int readChar(char* c) {
    if (scanf_s(" %c", c, 1) != 1) {
        printf("Input invalid.\n");
        clearInputBuffer();
        return 0;
    }
    return 1;
}

static void printMenu(void) {
    printf("\n=== Meniu ===\n");
    printf("1. Adauga medicament\n");
    printf("2. Sterge medicament\n");
    printf("3. Modifica medicament\n");
    printf("4. Afiseaza toate medicamentele\n");
    printf("5. Sortare\n");
    printf("6. Filtrare\n");
    printf("7. Undo\n");
    printf("8. Populare cu date de test\n");
    printf("0. Iesire\n");
    printf(">> ");
}

static void printMedicament(const Medicament* m) {
    printf("Cod: %d | Nume: %s | Conc: %.2f | Cant: %d\n",
        get_cod(m), get_nume(m),
        get_concentratie(m), get_cantitate(m));
}

static void printList(List* l) {
    if (l == NULL || sizeList(l) == 0) {
        printf("Lista vida.\n");
        return;
    }

    for (int i = 0; i < sizeList(l); i++) {
        printMedicament((Medicament*)getElem(l, i));
    }
}

static void uiAdd(UI* ui) {
    int cod, cant;
    float conc;
    char nume[128];

    printf("Cod: ");
    if (!readInt(&cod)) return;

    printf("Nume: ");
    if (!readString(nume, 128)) return;

    printf("Concentratie: ");
    if (!readFloat(&conc)) return;

    printf("Cantitate: ");
    if (!readInt(&cant)) return;

    int res = serviceAddMedicament(&ui->service, cod, nume, conc, cant);

    if (res == SERVICE_ADD_CREATED)
        printf("Adaugat.\n");
    else if (res == SERVICE_ADD_UPDATED)
        printf("Cantitate actualizata.\n");
    else if (res == SERVICE_VALIDATION_ERROR)
        printf("Date invalide.\n");
    else if (res == SERVICE_CONFLICT_ERROR)
        printf("Exista deja acest cod, dar cu alt nume sau alta concentratie.\n");
    else
        printf("Eroare.\n");
}

static void uiDelete(UI* ui) {
    int cod;

    printf("Cod: ");
    if (!readInt(&cod)) return;

    int res = serviceDeleteMedicament(&ui->service, cod);

    if (res == SERVICE_SUCCESS)
        printf("Sters.\n");
    else if (res == SERVICE_NOT_FOUND_ERROR)
        printf("Nu exista.\n");
    else
        printf("Eroare.\n");
}

static void uiUpdate(UI* ui) {
    int cod;
    float conc;
    char nume[128];

    printf("Cod: ");
    if (!readInt(&cod)) return;

    printf("Nume nou: ");
    if (!readString(nume, 128)) return;

    printf("Concentratie noua: ");
    if (!readFloat(&conc)) return;

    int res = serviceUpdateMedicament(&ui->service, cod, nume, conc);

    if (res == SERVICE_SUCCESS)
        printf("Actualizat.\n");
    else if (res == SERVICE_NOT_FOUND_ERROR)
        printf("Nu exista.\n");
    else if (res == SERVICE_VALIDATION_ERROR)
        printf("Date invalide.\n");
    else
        printf("Eroare.\n");
}

static void uiSort(UI* ui) {
    int criteriu, sens;
    List sorted;

    printf("1. Nume\n2. Cantitate\n>> ");
    if (!readInt(&criteriu)) return;

    printf("1. Crescator\n2. Descrescator\n>> ");
    if (!readInt(&sens)) return;

    FunctieComparare comp = (criteriu == 1) ? comparaNume : comparaCantitate;

    if (serviceSortGeneral(&ui->service, &sorted, comp, sens) == SERVICE_SUCCESS) {
        printList(&sorted);
        destroyList(&sorted);
    }
    else {
        printf("Eroare sortare.\n");
    }
}

static void uiFilter(UI* ui) {
    int opt;
    List filtered;

    printf("1. Cantitate < valoare\n");
    printf("2. Nume incepe cu litera\n");
    printf("3. Concentratie > valoare\n>> ");
    if (!readInt(&opt)) return;

    if (opt == 1) {
        int val;
        printf("Valoare: ");
        if (!readInt(&val)) return;

        if (serviceFilterStockLessThan(&ui->service, &filtered, val) == SERVICE_SUCCESS) {
            printList(&filtered);
            destroyList(&filtered);
        }
    }
    else if (opt == 2) {
        char lit;
        printf("Litera: ");
        if (!readChar(&lit)) return;

        if (serviceFilterNameStartsWith(&ui->service, &filtered, lit) == SERVICE_SUCCESS) {
            printList(&filtered);
            destroyList(&filtered);
        }
    }
    else if (opt == 3) {
        float val;
        printf("Valoare: ");
        if (!readFloat(&val)) return;

        if (serviceFilterConcentrationGreaterThan(&ui->service, &filtered, val) == SERVICE_SUCCESS) {
            printList(&filtered);
            destroyList(&filtered);
        }
    }
}

static void uiUndo(UI* ui) {
    int res = serviceUndo(&ui->service);

    if (res == SERVICE_SUCCESS)
        printf("Undo realizat.\n");
    else
        printf("Nu exista undo.\n");
}

static void uiPopulate(UI* ui) {
    serviceAddMedicament(&ui->service, 1, "Paracetamol", 500.0f, 10);
    serviceAddMedicament(&ui->service, 2, "Nurofen", 200.0f, 15);
    serviceAddMedicament(&ui->service, 3, "Aulin", 100.0f, 5);
    serviceAddMedicament(&ui->service, 4, "Ibuprofen", 400.0f, 20);
    serviceAddMedicament(&ui->service, 5, "Aspirina", 300.0f, 8);
    serviceAddMedicament(&ui->service, 6, "Coldrex", 250.0f, 12);
    serviceAddMedicament(&ui->service, 7, "Panadol", 500.0f, 25);
    serviceAddMedicament(&ui->service, 8, "Ketonal", 150.0f, 7);
    serviceAddMedicament(&ui->service, 9, "Nimesil", 100.0f, 9);
    serviceAddMedicament(&ui->service, 10, "Algocalmin", 500.0f, 30);

    printf("Date de test adaugate.\n");
}

UI createUI(void) {
    UI ui;
    ui.service = createService();
    return ui;
}

void destroyUI(UI* ui) {
    destroyService(&ui->service);
}

void runUI(UI* ui) {
    int cmd;

    while (1) {
        printMenu();

        if (!readInt(&cmd)) continue;

        switch (cmd) {
        case 1: uiAdd(ui); break;
        case 2: uiDelete(ui); break;
        case 3: uiUpdate(ui); break;
        case 4: printList(serviceGetAll(&ui->service)); break;
        case 5: uiSort(ui); break;
        case 6: uiFilter(ui); break;
        case 7: uiUndo(ui); break;
        case 8: uiPopulate(ui); break;
        case 0: return;
        default: printf("Comanda invalida.\n");
        }
    }
}
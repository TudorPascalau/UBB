#include "teste.h"

#include <stdio.h>

#include "teste_domain.h"
#include "teste_lista.h"
#include "teste_repository.h"
#include "teste_validare.h"
#include "teste_service.h"

void run_tests(void) {
    run_domain_tests();
    run_list_tests();
    run_repository_tests();
    run_validare_tests();
    run_service_tests();

    printf("Toate testele au rulat cu succes.\n");
}
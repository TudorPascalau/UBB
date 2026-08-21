#ifndef UI_H_
#define UI_H_

#include "service.h"

typedef struct {
    Service service;
} UI;

/*
* Creeaza UI-ul aplicatiei.
*/
UI createUI(void);

/*
* Distruge UI-ul.
*/
void destroyUI(UI* ui);

/*
* Ruleaza interfata utilizator.
*/
void runUI(UI* ui);

#endif
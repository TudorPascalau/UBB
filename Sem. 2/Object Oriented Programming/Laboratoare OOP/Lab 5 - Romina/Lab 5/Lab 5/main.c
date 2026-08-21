#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>

#include <stdio.h>
#include "teste.h"
#include "ui.h"

int main()
{
	run_tests();

	UI ui = createUI();
	runUI(&ui);
	destroyUI(&ui);

	_CrtDumpMemoryLeaks();

	return 0;
}
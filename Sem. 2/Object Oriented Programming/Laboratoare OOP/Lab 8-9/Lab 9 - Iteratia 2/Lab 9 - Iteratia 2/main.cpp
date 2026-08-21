#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>

#include <iostream>
using std::cout;

#include "TestAll.h"
#include "UI.h"
#include "FileRepo.h"
#include "Repo.h"
#include "RepoDict.h"

int main()
{
	TestAll testAll;
	testAll.test_all();
		
	{
		Repo repo;
		RepoDict repoDict{ 0.7 };
		FileRepo repoFile{ repo, "carti.txt" };
		Service srv{ repoFile };
		UI ui{ srv };

		ui.run();
	}

	if (_CrtDumpMemoryLeaks() == 1)
		cout << "S-a gasit memory leak";
	else cout << "Nu s-a gasit memory leak";

	return 0;
}

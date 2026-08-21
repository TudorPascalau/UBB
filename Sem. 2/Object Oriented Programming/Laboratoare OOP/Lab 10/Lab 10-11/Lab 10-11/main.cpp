#include "TestAll.h"
#include "Repo.h"
#include "FileRepo.h"
#include "Service.h"
#include "GUI.h"

#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

	TestAll test;
	test.test_all();

	Repo repo;
	FileRepo fileRepo{ repo, "carti.txt" };
	Service service{ fileRepo };

	GUI gui{service};
	gui.show();

    return app.exec();
}

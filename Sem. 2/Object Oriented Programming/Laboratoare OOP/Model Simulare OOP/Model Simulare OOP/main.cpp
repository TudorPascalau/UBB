#include "GUI.h"
#include "TestDomain.h"
#include "TestRepo.h"
#include "TestService.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    testDomain();
	testRepo();
    testService();

	Repo repo("rochii.txt");
	Service service(repo);

    GUI window(service);

    window.show();
    return app.exec();
}

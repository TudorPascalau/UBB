#include "GUI.h"
#include <QtWidgets/QApplication>

#include "Tester.h"
#include "Repo.h"
#include "Service.h"
#include "Validator.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

	Tester tester;
	tester.testTractor();
	tester.testRepo();
	tester.testValidator();
	tester.testService();

	Repo repo{ "tractoare.txt" };
	Validator val;
	Service service{ repo, val };

	GUI window{ service };
    window.show();
    return app.exec();
}

#include "GUI.h"
#include "Test.h"

#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
    
    Test t;
    t.testDomain();
	t.testRepository();
    t.testService();

    QApplication app(argc, argv);

	Repo repo("articole.txt");
	Service service(repo);
    GUI window(service);
    window.show();
    return app.exec();
}

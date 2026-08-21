#include "GUI.h"
#include <QApplication>
#include "TestDomain.h"

int main(int argc, char *argv[])
{
    testDomain();

    QApplication app(argc, argv);

	Repo repo("carti.txt");
    Service service(repo);

    GUI window(service);
    window.show();
    return app.exec();
}

#include "GUI.h"
#include <QtWidgets/QApplication>

#include "Tester.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    Tester t;
    t.testProdus();
    t.testRepo();
    t.testValidator();
    t.testService();

    Repo repo{ "produse.txt" };
    Validator val;
    Service srv{ repo, val };
    GUI window{srv};

    window.show();
    return app.exec();
}

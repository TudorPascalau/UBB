#include "GUI.h"
#include <QtWidgets/QApplication>

#include "Tester.h"

int main(int argc, char* argv[])
{
    QApplication app(argc, argv);

    Tester t;
    t.testMelodie();
    t.testRepo();
    t.testService();

    Repo repo{ "melodii.txt" };
    Service srv{ repo };
    GUI window{srv};

    window.show();
    return app.exec();
}

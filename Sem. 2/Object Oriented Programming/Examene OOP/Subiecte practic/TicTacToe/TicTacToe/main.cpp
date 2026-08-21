#include "GUI.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    Repo repo{ "jocuri.txt" };
    Validator val;
    Service srv{ repo, val };
    GUI window{srv};

    window.show();
    return app.exec();
}

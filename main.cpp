#include <QApplication>
#include "windowwidget.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    WindowWidget windowWidegt;

    windowWidegt.show();

    return a.exec();
}

#include "mw.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MW w;
    w.showMaximized();
    return a.exec();
}

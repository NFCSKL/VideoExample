#include "mymainwindow.h"
#include <QApplication>
#include "controller.h"


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Controller ctrl;
    return a.exec();
}

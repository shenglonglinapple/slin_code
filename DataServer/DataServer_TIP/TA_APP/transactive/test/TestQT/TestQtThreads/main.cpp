#include "mainwindow.h"
#include <QtGui/QApplication>
#pragma comment(lib,"ws2_32.lib")


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    return a.exec();
}

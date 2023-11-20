#include "mainwindow.h"
#include"secwindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
//    MainWindow w;
//    w.show();
    secWindow w;
    w.show();
    return a.exec();
}

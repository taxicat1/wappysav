#include "mainwindow.h"

#include <QApplication>

#include <QProcess>

#include <QFileDialog>

int main(int argc, char *argv[])
{
    QApplication wappysav(argc, argv);
    MainWindow w;
    w.show();
    return wappysav.exec();
    while (1){

    };
}

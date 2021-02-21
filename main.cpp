#include <string>
#include <iostream>
#include <ctime>

#include "operations.h"
#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <Windows.h>

#include <QApplication>


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}

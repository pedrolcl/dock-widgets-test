/**
 * Copyright (c) 2023, Pedro López-Cabanillas
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "mainwindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QCoreApplication::setApplicationName("TestDockWidgets");
    QCoreApplication::setOrganizationDomain("tests.github.io");
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}

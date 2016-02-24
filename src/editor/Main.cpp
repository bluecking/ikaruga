/*
 * Main.cpp
 *
 *  Created on: Jul 23, 2015
 *      Author: twiemann
 */

#include <QtGui>

#include "EditorMainWindow.hpp"

int main(int argc, char** argv)
{
    QApplication app(argc, argv);

    MainWindow mainWindow;
    mainWindow.show();

    return app.exec();
}



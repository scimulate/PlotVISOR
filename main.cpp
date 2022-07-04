/*
PlotVISOR is a visual assistant for interpreting colored contour plots.
Copyright (C) 2022 Scimulate LLC (Samuel Jacobs)

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <https://www.gnu.org/licenses/>.
*/

#include "mainwindow.h"

#include <QApplication>
#include <QSplashScreen>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    QSplashScreen *splash = new QSplashScreen;
    //splash->setPixmap(QPixmap(":/images/splash.png"));
    splash->show();

    //QSplashScreen *splash;
    //splash->showMessage("Test");
    //splash.showMessage("test");
    //splash.showMessage("test");
    //app.processEvents();

    MainWindow w;
    w.show();
    return app.exec();
}

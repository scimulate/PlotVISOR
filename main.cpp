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

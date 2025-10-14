#include "mainwindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QIcon appIcon(":/appIcon/assets/QlackjackIcon.png");    // Create the app icon
    a.setWindowIcon(appIcon);   // Set the app icon
    MainWindow w;
    w.show();
    return a.exec();
}

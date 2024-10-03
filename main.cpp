#include "views/mainwindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication evaliqApp(argc, argv);
    evaliqApp.setStyle("fusion");
    MainWindow mainWindow;
    mainWindow.show();
    return evaliqApp.exec();
}

#include "views/mainwindow.h"

#include <QApplication>
#include <QQuickStyle>

int main(int argc, char *argv[])
{
    QApplication evaliqApp(argc, argv);
    QQuickStyle::setStyle("Material");
    evaliqApp.setStyle("fusion");
    MainWindow mainWindow;
    mainWindow.show();
    return evaliqApp.exec();
}

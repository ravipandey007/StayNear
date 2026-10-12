#include <QApplication>

#include "MainWindow.h"

// Start Qt and show the main StayNear window.
int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    MainWindow window;
    window.show();

    return app.exec();
}

#include "mainwindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    // Set the shared open gl context. Without this the project won't run on DI5.
    QApplication::setAttribute(Qt::AA_ShareOpenGLContexts);

    // Set the environment variable to change the platform abstraction. Without this the project won't run on DI5.
    qputenv("QT_QPA_PLATFORM", QByteArray("wayland-egl"));

    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}

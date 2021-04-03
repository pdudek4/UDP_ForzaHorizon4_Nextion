#include "mainwindow.h"
#include "myudp.h"


#include <QApplication>
#include <QDebug>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;

    MyUDP udp_o;
    w.clientUDP = &udp_o;

    w.show();

    return a.exec();
}

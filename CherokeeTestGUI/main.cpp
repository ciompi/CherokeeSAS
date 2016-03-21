#include "mainwindow.h"
#include <QApplication>
#include <RTIMULib.h>
#include <QString>
#include <imuthread.h>


int main(int argc, char *argv[])
{

    IMUThread imuthread;
    imuthread.start();

    QApplication a(argc, argv);

    //create the window
    MainWindow w;
    w.show();

    //execture the application
    w.startTimer(200);
    return a.exec();

}

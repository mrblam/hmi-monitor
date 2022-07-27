#include <QCoreApplication>
#include <iostream>
#include "interprocesscom.h"
#include "monitor.h"
int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    std::cout << "hello" <<std::endl;
    InterProcessCom *ICP = new InterProcessCom();
    Monitor hmiMonitor(ICP);
    return a.exec();
}

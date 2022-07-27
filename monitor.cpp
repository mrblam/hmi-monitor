#include "monitor.h"

Monitor::Monitor(InterProcessCom *p_ipc,QObject *parent) : QObject(parent)
{
    CurrentVersion = new QProcess();
    this->IPC = p_ipc;
    this->isStart = false;
    connect (&ScanningFrequency, &QTimer::timeout, this,&Monitor::Scan);
    ScanningFrequency.start(5000);
}

void Monitor::Scan()
{
    qDebug() << "show" << CurrentVersion->state();
    this->isStart = IPC->getReStart();
    qDebug() << this->isStart;
    if(CurrentVersion->state() == 0 || this->isStart == true){
        this->openCurrentVersion();

        qDebug() <<  "restart bss-hmi "  ;
        return;
    }

}

void Monitor::openCurrentVersion()
{
    QString currentProgram = "/home/hoanpx/Desktop/build-bss-hmi-Desktop-Release/bss-hmi";
    CurrentVersion->start(currentProgram);
    qDebug() << "show" << CurrentVersion->state();
}

#include "interprocesscom.h"

InterProcessCom::InterProcessCom(QObject *parent) : QObject(parent)
{
    socket = new QTcpSocket();
    connect(socket, &QIODevice::readyRead,this,&InterProcessCom::readMessage);
    connect(&heartbeatsend,&QTimer::timeout,this,&InterProcessCom::connectToBssHmi);
    heartbeatsend.start(5000);
}

bool InterProcessCom::getReStart()
{
    return reStart;
}

void InterProcessCom::readMessage()
{
    socket->waitForReadyRead(2000);
    qDebug() << "Bytes available : " << socket->bytesAvailable();
    qDebug() << "Du lieu nhan duoc tu bss-hmi la : " << socket->readAll();
//  serverRead->close();
}

void InterProcessCom::connectToBssHmi()
{
    socket->abort();
    socket->connectToHost("localhost",TCP_SERVER_PORT_READ);
    qDebug() <<socket->openMode();
    if(socket->waitForConnected(1000))
    {
        qDebug() << "bss-hmi connected "  ;
        reStart = false;
    }
    else
    {
        qDebug() << "Reconnect" ;
        reStart = true;
    }
}

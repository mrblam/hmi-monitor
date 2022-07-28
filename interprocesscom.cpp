#include "interprocesscom.h"

InterProcessCom::InterProcessCom(QObject *parent) : QObject(parent)
{
    server = new QTcpServer(this);
    //socket = new QTcpSocket(this);
    connect(server, SIGNAL(newConnection()), this, SLOT(newConnection()));
    if (!this->server->listen(QHostAddress::AnyIPv4,TCP_SERVER_PORT_WRITE))
    {
        qDebug() << tr("Unable to start the server: %1.").arg(server->errorString()) ;
        return;
    }
    qDebug() << "  port is " << server->serverPort();
    connect(server,&QTcpServer::newConnection, this, &InterProcessCom::serverRespone);
//    connect(&heartbeatSend,&QTimer::timeout, this, &connectMonitor::sendMessage);
//    heartbeatSend.start(1000)
}

void InterProcessCom::serverRespone()
{
    socket = server->nextPendingConnection();
    socket->waitForReadyRead();
    qDebug()<<socket->readAll();
    socket->write("server respone");
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
//    socket->close();
}



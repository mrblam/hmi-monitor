#include "interprocesscom.h"

InterProcessCom::InterProcessCom(QObject *parent) : QObject(parent)
{
    server = new QTcpServer(this);
//    socket = new QTcpSocket(this);
    connect(server, SIGNAL(newConnection()), this, SLOT(newConnection()));
    if (!this->server->listen(QHostAddress::AnyIPv4,TCP_SERVER_PORT_WRITE))
    {
        qDebug() << tr("Unable to start the server: %1.").arg(server->errorString()) ;
        return;
    }
    qDebug() << "  port is " << server->serverPort();
    connect(server,&QTcpServer::newConnection, this, &InterProcessCom::serverRespone);
    connect(&heartbeatSys,&QTimer::timeout, this, &InterProcessCom::checkSys);
    heartbeatSys.start(1000);
}

void InterProcessCom::serverRespone()
{
    disconnectEvent = 0;
    socket = server->nextPendingConnection();
    socket->waitForReadyRead();
//    qDebug()<<socket->readAll();
    buffer.append(socket->readAll());
    checkRequest();
    socket->write("Server Respones : Hello Client");
}


bool InterProcessCom::getReStart()
{
    return reStart;
}

void InterProcessCom::checkRequest()
{
    int32_t start  = buffer.indexOf(SOM);
    int32_t finish = buffer.indexOf(EOM);

    QByteArray pack = buffer.mid(start+1,finish-start-1);
    qDebug()<< "Client send: " +pack;
    buffer.clear();

    QList<QByteArray> fields=pack.split(FIELD_DELIMITER);
    system =fields.at(0);
    ui = fields.at(1);
    state = fields.at(2);
    sSystem = system;
    sUi = ui;
    sState = state;

}

void InterProcessCom::checkSys()
{
    disconnectEvent ++;
    qDebug()<< "connectEvent" <<disconnectEvent;
    qDebug()<<sSystem << sUi<< sState<< countSubCmd;

#if 0
    if(sUi == 'D') // trang thai mac dinh
    {

    }
    if(sUi == 'U') // trang thai co nguoi su dung - giao dien thay doi
    {

    }
#endif


#if 1
    if(sState == 'O') // dem thoi gian ui nao day open
    {
        countSubCmd++;
    }
    if (sState == 'C' || disconnectEvent == 0)
    {
        sUi = "";
        sState = "";
        countSubCmd = 0;
    }
    if(countSubCmd > 20 )//|| disconnectEvent > 10
    {
        countSubCmd = 0;
        sState = "";
        reStart = true;
        qDebug() << "countSubCmd" <<countSubCmd;

        //treo giao dien,treo he thong,reset he thong
    }
    if(sSystem == 'S')
    {
        sSystem = "";
        reStart = false;
    }
#endif
}






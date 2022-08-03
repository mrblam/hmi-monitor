#ifndef INTERPROCESSCOM_H
#define INTERPROCESSCOM_H

#include <QObject>
#include <QTimer>
#include <QTcpServer>
#include <QTcpSocket>

// IPC app1 (server) --- HMI (client)
#define TCP_SERVER_PORT_WRITE 12345
// IPC app1 (client) --- HMI (server)
#define TCP_SERVER_PORT_READ  54321
#define SOM ':'
#define EOM '*'
#define FIELD_DELIMITER ','
#define UI_CHANGE        'UI'
#define HEART_BEAT       'HB'
class InterProcessCom : public QObject
{
    Q_OBJECT
public:
    InterProcessCom(QObject *parent = nullptr);

public:
    void serverRespone();
    bool reStart;
    bool getReStart();
    void offReStart();
    void checkRequest();
    QByteArray system;
    QByteArray ui;
    QByteArray state;
public slots:
    void checkSys();
    void resetUi();

private:
    int disconnectEvent;
    int countSubCmd;
    QString sSystem;
    QString sUi;
    QString sState;
    QTimer heartbeatSys;
    QTimer monitorUi;
    QByteArray buffer;
    QTimer heartbeatsend;
    void initServer();
    QString ipAddress;
    QTcpServer *server;
    QTcpSocket *socket;


};

#endif // INTERPROCESSCOM_H

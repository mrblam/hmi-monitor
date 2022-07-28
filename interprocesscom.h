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

class InterProcessCom : public QObject
{
    Q_OBJECT
public:
    InterProcessCom(QObject *parent = nullptr);

public:
    void serverRespone();
    bool reStart;
    bool getReStart();
private slots:

    void readMessage();

private:
    QTimer heartbeatsend;
    void initServer();
    QString ipAddress;
    QTcpServer *server;
    QTcpSocket *socket;


};

#endif // INTERPROCESSCOM_H

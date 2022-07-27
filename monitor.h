#ifndef MONITOR_H
#define MONITOR_H

#include <QObject>
#include <QTimer>
#include <interprocesscom.h>
#include <QProcess>

class Monitor : public QObject
{
    Q_OBJECT
public:
    explicit Monitor(InterProcessCom *p_ipc = nullptr,QObject *parent = nullptr);

signals:

private slots:
    void Scan();
    void openCurrentVersion();

private:
    QTimer ScanningFrequency;
    bool isStart;
    InterProcessCom *IPC;
    QProcess *CurrentVersion;

};

#endif // MONITOR_H

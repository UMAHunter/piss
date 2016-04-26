#ifndef PISSTRANSMISSIONTASK_H
#define PISSTRANSMISSIONTASK_H

#include <QThread>
#include <QObject>
#include <QTcpSocket>
#include <QTimer>
#include "Devices.h"
#include "OutputQueue.h"


class pissTransmissionTask : public QObject
{
    Q_OBJECT
private:
    QTcpSocket* socketTransmission;
    QVector <OutputQueue*> *oq;
    Devices *environment;
    QTimer *transmissionTimer;
    int frameCounter;
    QMutex outputMutex;
public:
    pissTransmissionTask(QVector <OutputQueue*> *oq, Devices* environment);
    ~pissTransmissionTask();
    void connectTo(int moduleNumber);
public slots:
    void startTransfer();
    void transfer();
};

#endif // PISSTRANSMISSIONTASK_H

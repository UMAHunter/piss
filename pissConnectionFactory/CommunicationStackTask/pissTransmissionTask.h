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

public:


private:
    QTcpSocket* socketTransmission;
    QVector <OutputQueue*> *oq;
    Devices *devices;
    QTimer *transmissionTimer;
    int frameCounter;
    QMutex outputMutex;
    int id;

public:
    pissTransmissionTask(int id, QVector <OutputQueue*> *oq, Devices* devices, QTcpSocket* socketTransmission);
    ~pissTransmissionTask();

public slots:
    void launch();
    void transfer();
};

#endif // PISSTRANSMISSIONTASK_H

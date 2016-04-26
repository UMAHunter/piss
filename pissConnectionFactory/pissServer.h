#ifndef PISSSERVER_H
#define PISSSERVER_H

#include <QTcpServer>
#include <QVector>
#include <QMessageBox>

#include "Devices.h"
#include "pissReceptionTask.h"
#include "DatagrammeAnalyser.h"
#include "pissInputInformationDecoder.h"

/**
 * @brief The pissServer class
 */
class pissServer : public QTcpServer
{
    Q_OBJECT
public:
    pissServer(QVector <InputQueue*> *inputQueueManager,
               QVector <OutputQueue*> *outputQueueManager,
               Devices* networkEnvironment,
               DatagrammeAnalyser *datagrammeAnalyser,
               GlobalTime *globalTime);

    ~pissServer();
    bool launchServer();
    bool stopServer();
    bool getConnectionState();

private:

    bool serverStatus;

    Devices *networkEnvironment;
    QVector <InputQueue*> *inputQueueManager;
    QVector <OutputQueue*> *outputQueueManager;
    DatagrammeAnalyser *datagrammeAnalyser;
    GlobalTime *globalTime;

protected:
    int id;
    void incomingConnection(qintptr socket);
};

#endif // PISSSERVER_H

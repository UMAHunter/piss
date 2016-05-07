#ifndef PISSCOMMUNICATIONSTACK_H
#define PISSCOMMUNICATIONSTACK_H

#include "pissInputInformationDecoder.h"
#include "pissOutputInformationEncoder.h"
#include "Devices.h"
#include "DatagrammeAnalyser.h"
#include "InputQueue.h"
#include "OutputQueue.h"
#include "pissServer.h"
#include "GlobalTime.h"
#include "igtClient.h"
#include "SystemDataBase.h"


/**
 * @brief The pissCommunicationStack class
 */
class pissCommunicationStack
{
private:
    Devices *devices;
    QVector <InputQueue*> inputQueueManager;
    QVector <OutputQueue*> outputQueueManager;
    DatagrammeAnalyser *datagrammeAnalyser;
    pissInputInformationDecoder *informationDecodeTask;
    pissOutputInformationEncoder *outputInformationEncoder;
    pissServer *server;
    GlobalTime *globalTime;

    //!
    SystemDataBase* database;

public:
    bool launchServer();
    bool connectBack(bool flag, QString addr, int port);
    bool closeServer();
    void clearBuffer();
    Device* getSelf();

    void setDatabase(SystemDataBase* database);

public:
    pissCommunicationStack(GlobalTime *globalTime);
};

#endif // PISSCOMMUNICATIONSTACK_H

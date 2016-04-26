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
#include "Patient.h"
#include "SystemMetaData.h"


class pissCommunicationStack
{
private:
    Devices *networkEnvironment;
    QVector <InputQueue*> inputQueueManager;
    QVector <OutputQueue*> outputQueueManager;
    DatagrammeAnalyser *datagrammeAnalyser;
    pissInputInformationDecoder *informationDecodeTask;
    pissOutputInformationEncoder *outputInformationEncoder;
    pissServer *server;
    GlobalTime *globalTime;

    Patient *patientHandling;
    SystemMetaData *systemMetaData;

public:
    bool launch();
    bool closeServer();

    void clearBuffer();
    void setPatientHandling(Patient *patientHandling);
    void setSystemMetaData(SystemMetaData *systemMetaData);

    Devices* getNetworkEnvironment();
public:
    pissCommunicationStack(GlobalTime *globalTime);
};

#endif // PISSCOMMUNICATIONSTACK_H

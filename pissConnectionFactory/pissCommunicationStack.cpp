#include "pissCommunicationStack.h"

pissCommunicationStack::pissCommunicationStack(GlobalTime *globalTime)
{
    this->globalTime = globalTime;

    networkEnvironment = new pissNetworkEnvironment();
    networkEnvironment->append(0, 10703);

    datagrammeAnalyser = new DatagrammeAnalyser(&outputQueueManager,&inputQueueManager,networkEnvironment,globalTime);
    informationDecodeTask = new pissInputInformationDecoder(&inputQueueManager,networkEnvironment,datagrammeAnalyser);
    server = new pissServer(&inputQueueManager,&outputQueueManager,networkEnvironment, datagrammeAnalyser,globalTime);
}

void pissCommunicationStack::clearBuffer(){
    inputQueueManager.clear();
    outputQueueManager.clear();
}

void pissCommunicationStack::launch(){
    informationDecodeTask->start();
    server->launchServer();
}

void pissCommunicationStack::setPatientHandling(Patient *patientHandling){
    this->patientHandling = patientHandling;
}

void pissCommunicationStack::setSystemMetaData(SystemMetaData *systemMetaData){
    this->systemMetaData = systemMetaData;
}

#include "pissCommunicationStack.h"


/**
 * @brief pissCommunicationStack::pissCommunicationStack
 * @param globalTime
 */
pissCommunicationStack::pissCommunicationStack(GlobalTime *globalTime)
{
    this->globalTime = globalTime;

    networkEnvironment = new pissNetworkEnvironment();
    networkEnvironment->append(0, 10703);

    datagrammeAnalyser = new DatagrammeAnalyser(&outputQueueManager,&inputQueueManager,networkEnvironment,globalTime);
    informationDecodeTask = new pissInputInformationDecoder(&inputQueueManager,networkEnvironment,datagrammeAnalyser);
    outputInformationEncoder = new pissOutputInformationEncoder();
    server = new pissServer(&inputQueueManager,&outputQueueManager,networkEnvironment, datagrammeAnalyser,globalTime);
}

//! -------------------------------------------------------------------------------------------------------------------
//!
//! \brief pissCommunicationStack::clearBuffer
//!
void pissCommunicationStack::clearBuffer(){
    inputQueueManager.clear();
    outputQueueManager.clear();
}

//! -------------------------------------------------------------------------------------------------------------------
//!
//! \brief pissCommunicationStack::closeServer
//! \return
//!
bool pissCommunicationStack::closeServer(){
    informationDecodeTask->stop();
    //outputInformationEncoder->stop();
    return server->stopServer();
}

//! -------------------------------------------------------------------------------------------------------------------
//!
//! \brief pissCommunicationStack::launch
//!
bool pissCommunicationStack::launch(){
    informationDecodeTask->start();
    outputInformationEncoder->start();
    return server->launchServer();
}

//! -------------------------------------------------------------------------------------------------------------------
//!
//! \brief pissCommunicationStack::setPatientHandling
//! \param patientHandling
//!
void pissCommunicationStack::setPatientHandling(Patient *patientHandling){
    this->patientHandling = patientHandling;
}

//! -------------------------------------------------------------------------------------------------------------------
//!
//! \brief pissCommunicationStack::setSystemMetaData
//! \param systemMetaData
//!
void pissCommunicationStack::setSystemMetaData(SystemMetaData *systemMetaData){
    this->systemMetaData = systemMetaData;
}

//!
//! \brief pissCommunicationStack::getNetworkEnvironment
//! \return
//!
pissNetworkEnvironment* pissCommunicationStack::getNetworkEnvironment(){
    return this->networkEnvironment;
}

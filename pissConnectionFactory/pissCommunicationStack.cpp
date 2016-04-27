#include "pissCommunicationStack.h"


/**
 * @brief pissCommunicationStack::pissCommunicationStack
 * @param globalTime
 */
pissCommunicationStack::pissCommunicationStack(GlobalTime *globalTime)
{
    this->globalTime = globalTime;

    devices = new Devices();
    devices->append(0, 10703);

    datagrammeAnalyser = new DatagrammeAnalyser(&outputQueueManager,&inputQueueManager,devices,globalTime);
    informationDecodeTask = new pissInputInformationDecoder(&inputQueueManager,devices,datagrammeAnalyser);
    outputInformationEncoder = new pissOutputInformationEncoder();
    server = new pissServer(&inputQueueManager,&outputQueueManager,devices, datagrammeAnalyser,globalTime);
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
bool pissCommunicationStack::launchServer(){
    informationDecodeTask->start();
    outputInformationEncoder->start();
    return server->launchServer();
}

//! -------------------------------------------------------------------------------------------------------------------
//!
//! \brief pissCommunicationStack::connectBack
//! \param flag
//! \param addr
//! \param port
//! \return
//!
bool pissCommunicationStack::connectBack(bool flag, QString addr, int port){
    if(flag){
        //! motivate connect
        igtClient *client = new igtClient(this->devices->getClientNumber()-1,&outputQueueManager,devices);
        client->connect_request(addr, port);
    }
    else{
        //! connect back process
    }

    return true;
}

//! -------------------------------------------------------------------------------------------------------------------
//!
//! \brief pissCommunicationStack::getNetworkEnvironment
//! \return
//!
Devices* pissCommunicationStack::getNetworkEnvironment(){
    return this->devices;
}

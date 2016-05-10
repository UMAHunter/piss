#include "pissCommunicationStack.h"


/**
 * @brief pissCommunicationStack::pissCommunicationStack
 * @param globalTime
 */
pissCommunicationStack::pissCommunicationStack(GlobalTime *globalTime)
{
    this->globalTime = globalTime;

    this->devices = new Devices();
    this->devices->setMyListenPort(10703);

    this->datagrammeAnalyser = new DatagrammeAnalyser(&outputQueueManager,&inputQueueManager,devices,globalTime, database);
    this->informationDecodeTask = new pissInputInformationDecoder(&inputQueueManager,devices,datagrammeAnalyser);
    this->outputInformationEncoder = new pissOutputInformationEncoder();
    this->server = new pissServer(&inputQueueManager,&outputQueueManager,devices, datagrammeAnalyser,globalTime, database);
}

//! -------------------------------------------------------------------------------------------------------------------
//!
//! \brief pissCommunicationStack::setDatabase
//! \param database
//!
void pissCommunicationStack::setDatabase(SystemDataBase* database){
    this->database = database;
    //this->database->setDevices(this->devices)
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
    //outputInformationEncoder->start();
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
Device* pissCommunicationStack::getSelf(){
    return this->devices->getSelf();
}

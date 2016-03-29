#include "pissServer.h"


/**
 * @brief pissServer::pissServer
 * @param inputQueueManager
 * @param NetworkEnvironment
 * @param datagrammeAnalyser
 */
pissServer::pissServer(QVector <InputQueue*> *inputQueueManager,
                       QVector <OutputQueue*> *outputQueueManager,
                       pissNetworkEnvironment *networkEnvironment,
                       DatagrammeAnalyser *datagrammeAnalyser,
                       GlobalTime *globalTime)
{
    this->serverStatus = false;
    this->id = 0;
    this->inputQueueManager = inputQueueManager;
    this->outputQueueManager = outputQueueManager;
    this->networkEnvironment = networkEnvironment;
    this->datagrammeAnalyser = datagrammeAnalyser;
    this->globalTime = globalTime;
}

//!--------------------------------------------------------------------------------------------------------------------------------
//!
//! \brief pissServer::~pissServer
//!
pissServer::~pissServer(){

}

//!--------------------------------------------------------------------------------------------------------------------------------
//!
//! \brief pissServer::stopServer
//! \return
//!
bool pissServer::stopServer(){
    if(serverStatus){

        //! TODO stop task related and queues...........

        this->close();
        return true;
    }
    else{
        QMessageBox msgBox;
        msgBox.setText("server do not need to stop, hasn't been launched");
        msgBox.exec();
        return false;
    }
    return false;
}

//!--------------------------------------------------------------------------------------------------------------------------------
//!
//! \brief pissServer::launchServer
//!
bool pissServer::launchServer(){
    if(serverStatus){
        QMessageBox msgBox;
        msgBox.setText("Server already in listening...");
        msgBox.exec();
        return false;
    }

    serverStatus = this->listen(QHostAddress::Any, this->networkEnvironment->getPortByModule(0));
    return serverStatus;
}

//!--------------------------------------------------------------------------------------------------------------------------------
//!
//! \brief pissServer::getConnectionState
//!
bool pissServer::getConnectionState(){
    return serverStatus;
}

//!--------------------------------------------------------------------------------------------------------------------------------
//!
//! \brief pissServer::incomingConnection
//! \param socketDescriptor
//!
void pissServer::incomingConnection(qintptr socketDescriptor){ 
    this->networkEnvironment->addAClient();

    InputQueue *myInputQueue = new InputQueue();
    myInputQueue->clear();
    OutputQueue *myOutputQueue = new OutputQueue();
    myOutputQueue->clear();

    inputQueueManager->push_back(myInputQueue);
    outputQueueManager->push_back(myOutputQueue);

    pissReceptionTask *receptionTask = new pissReceptionTask(id,
                                                             socketDescriptor,
                                                             datagrammeAnalyser,
                                                             inputQueueManager,
                                                             networkEnvironment);

    receptionTask->start();

    id++;
}

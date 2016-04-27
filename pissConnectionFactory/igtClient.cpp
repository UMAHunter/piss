#include "igtClient.h"


/**
 * @brief igtClient::igtClient
 * @param oq
 * @param devices
 */
igtClient::igtClient(int id, QVector <OutputQueue*> *oq, Devices* devices){
    this->id = id;

    motivateConnectionRequest = true;

    socket = new QTcpSocket();

    transmissionTask = new pissTransmissionTask(this->id, oq, devices, socket);

    this->connect(this->socket, SIGNAL(connected()), this, SLOT(startTransfer()));
}

//! ---------------------------------------------------------------------------------
//!
//! \brief igtClient::connect_request
//! \param addr
//! \param port
//!
void igtClient::connect_request(QString addr, int port){
    motivateConnectionRequest = true;
    socket->connectToHost(addr, port);
}

//! ---------------------------------------------------------------------------------
//!
//! \brief igtClient::connectBackRequest
//! \param addr
//! \param port
//!
void igtClient::connectBackRequest(QString addr, int port){
    motivateConnectionRequest = false;
    socket->connectToHost(addr, port);
}

//! ---------------------------------------------------------------------------------
//!
//! \brief igtClient::startTransfer
//!
void igtClient::startTransfer(){

    if(motivateConnectionRequest){
        //!todo directly send handshake msg

        transmissionTask->launch();
    }
    else{
        transmissionTask->launch();

        //! genrate a handshake commit msg push into oq....
        //! this->oq.at(id).append(handshake commit)
    }

}


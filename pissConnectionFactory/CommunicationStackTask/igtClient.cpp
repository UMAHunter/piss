#include "igtClient.h"


/**
 * @brief igtClient::igtClient
 * @param oq
 * @param devices
 */
igtClient::igtClient(int id, QVector <OutputQueue*> *oq, Devices* devices){
    this->id = id;
    this->devices = devices;
    motivateConnectionRequest = true;

    soc = new QTcpSocket();

    transmissionTask = new pissTransmissionTask(this->id, oq, devices, soc);

    this->connect(this->soc, SIGNAL(connected()), this, SLOT(startTransfer()));
}

//! ---------------------------------------------------------------------------------
//!
//! \brief igtClient::connect_request
//! \param addr
//! \param port
//!
void igtClient::connect_request(QString addr, int port){
    motivateConnectionRequest = true;
    soc->connectToHost(addr, port);
}

//! ---------------------------------------------------------------------------------
//!
//! \brief igtClient::connectBackRequest
//! \param addr
//! \param port
//!
void igtClient::connectBackRequest(QString addr, int port){
    motivateConnectionRequest = false;
    soc->connectToHost(addr, port);
}

//! ---------------------------------------------------------------------------------
//!
//! \brief igtClient::startTransfer
//!
void igtClient::startTransfer(){

    devices->setSocketTransById(id, soc->socketDescriptor());

    if(motivateConnectionRequest){
        //!todo directly send handshake msg
//        HandShakeMessage msg;
//        msg.setDataType();
//        ...

        //soc->write( msg.toDatagramme().getValue())

        transmissionTask->launch();
    }
    else{
        transmissionTask->launch();

        //! genrate a handshake commit msg push into oq....
        //! this->oq.at(id).append(handshake commit)
    }

}


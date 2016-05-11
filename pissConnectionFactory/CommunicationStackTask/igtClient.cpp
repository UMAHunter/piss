#include "igtClient.h"


/**
 * @brief igtClient::igtClient
 * @param oq
 * @param devices
 */
igtClient::igtClient(int id, QVector <OutputQueue*> *oq, Devices* devices, GlobalTime *globalTime){
    this->id = id;
    this->devices = devices;
    this->globalTime = globalTime;
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
    qDebug()<<addr<<port;
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

//        HandShakeMessage *msg = new HandShakeMessage();

//        msg->setDataType(1);
//        msg->setDeviceId(0);
//        msg->setTimestamp(globalTime->GetMicroS());
//        msg->setDLC(38);
//        msg->setDeviceName("communication stack");
//        msg->setLocalIP(127, 12, 15, 30);
//        msg->setLocalPort(2630);

//        soc->write(msg->toCDatagram());
//        soc->flush();
        //soc->waitForBytesWritten(-1);
        transmissionTask->launch();
    }
    else{
        qDebug()<<"back";
        transmissionTask->launch();

        //! genrate a handshake commit msg push into oq....
        //! this->oq.at(id).append(handshake commit)
    }

}



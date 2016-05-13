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
    this->motivateConnectionRequest = true;

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
qintptr igtClient::connect_request(QString addr, int port){
    motivateConnectionRequest = true;
    soc->connectToHost(addr, port);
    qDebug()<<addr<<port;
    return soc->socketDescriptor();
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

    //devices->setSocketTransById(id, soc->socketDescriptor());

    if(motivateConnectionRequest){
        HandShakeMessage *msg = new HandShakeMessage();

        msg->setDataType(1);
        msg->setDeviceId(id);
        msg->setTimestamp(globalTime->GetMicroS());
        msg->setDLC(38);
        msg->setDeviceName("communication stack");
        msg->setIP(127, 12, 15, 30);
        msg->setPort(2630);

        soc->write(msg->toCDatagram());
        soc->flush();
        //soc->waitForBytesWritten(-1);
    }
    else{
        HandShakeCommitMessage *cmsg = new HandShakeCommitMessage();
        cmsg->setDataType(2);
        cmsg->setDeviceId(id);
        cmsg->setTimestamp(globalTime->GetMicroS());
        cmsg->setDLC(32);
        cmsg->setDeviceName("platform");

        CDatagramme *datagram = new CDatagramme();
        datagram->setValue(&cmsg->toCDatagram());

        this->oq->at(id)->append(datagram);
    }
    transmissionTask->launch();
}



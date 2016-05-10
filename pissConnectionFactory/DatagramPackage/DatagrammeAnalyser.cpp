#include "DatagrammeAnalyser.h"

DatagrammeAnalyser::DatagrammeAnalyser(QVector <OutputQueue*> *oq,
                                       QVector <InputQueue*> *iq,
                                       Devices* environment,
                                       GlobalTime *globalTime,
                                       SystemDataBase* database)
{
    this->iq = iq;
    this->oq = oq;
    this->devices = environment;
    this->globalTime = globalTime;
    this->database = database;
}

DatagrammeAnalyser::~DatagrammeAnalyser()
{

}

//! ----------------------------------------------------------------------------------------
//!
//! \brief DatagrammeAnalyser::encodage
//! \param modulename
//!
void DatagrammeAnalyser::encodage(QString modulename)
{

}

//! ----------------------------------------------------------------------------------------
//!
//! \brief DatagrammeAnalyser::decodage
//! \param id
//! \param datagramme
//!
void DatagrammeAnalyser::decodage(int id, CDatagramme *datagramme){

    switch (datagramme->getDataType()){
        case HelloMessage: {
            qDebug()<<"HelloMessage";
            decodeHelloMessage(id, datagramme);
            break;
        }
        case HandShakeMessage:{
            qDebug()<<"HandShakeMessage";
            decodeHandShakeMessage(id, datagramme);
            break;
        }
        case CTImage:{
            qDebug()<<"CTImage";
            decodeCTImage(datagramme);
            break;
        }
    }
    qDebug()<<"end decoding process";
}

//! ----------------------------------------------------------------------------------------
//!
//! \brief DatagrammeAnalyser::decodeHelloMessage
//! \param id
//! \param datagramme
//!
void DatagrammeAnalyser::decodeHelloMessage(int id, CDatagramme *datagramme){
    datagramme->setTimestamp(globalTime->GetMicroS());
    oq->at(id)->append(datagramme);
}

//! ----------------------------------------------------------------------------------------
//!
//! \brief DatagrammeAnalyser::decodeHandShakeMessage
//! \param id
//! \param datagramme
//!
//! handshake msg format: + + +
//!
void DatagrammeAnalyser::decodeHandShakeMessage(int id, CDatagramme *datagramme){
    qDebug()<<"decode handshakemsg task"<<datagramme->getValue()->length();

    long long i = datagramme->getValue()->at(6)*long long(pow(2,32))+
            datagramme->getValue()->at(5)*long long(pow(2,24))
           +datagramme->getValue()->at(4)*long long(pow(2,16))
           +datagramme->getValue()->at(3)*long long(pow(2,8))
           +datagramme->getValue()->at(2);
    qDebug()<<i<<datagramme->getDLC();
    for(int cpt = 0 ; cpt <datagramme->getDLC(); cpt++ ){
        qDebug()<<unsigned char(datagramme->getValue()->at(cpt));
    }



//    HandShakeMessage *msg = new HandShakeMessage();
//    msg->decodeDatagram(datagramme);

//    igtClient *client = new igtClient(id, this->oq, this->devices);
//    client->connectBackRequest(msg.ip, msg.port);

  //  this->database->notify();
}

//! ----------------------------------------------------------------------------------------
//!
//! \brief DatagrammeAnalyser::decodeCTImage
//! \param datagramme
//!
void DatagrammeAnalyser::decodeCTImage(CDatagramme *datagramme){

}


#include "DatagrammeAnalyser.h"

DatagrammeAnalyser::DatagrammeAnalyser(QVector <OutputQueue*> *oq,
                                       QVector <InputQueue*> *iq,
                                       Devices* environment,
                                       GlobalTime *globalTime)
{
    this->iq = iq;
    this->oq = oq;
    this->devices = environment;
    this->globalTime = globalTime;
}

DatagrammeAnalyser::~DatagrammeAnalyser()
{

}

void DatagrammeAnalyser::encodage(QString modulename)
{

}

void DatagrammeAnalyser::decodage(int id, CDatagramme *datagramme){

    switch (datagramme->getID()){
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
    datagramme->modifierTimestamp(globalTime->GetMicroS());
    oq->at(id)->append(datagramme);
}

//! ----------------------------------------------------------------------------------------
//!
//! \brief DatagrammeAnalyser::decodeHandShakeMessage
//! \param id
//! \param datagramme
//!
void DatagrammeAnalyser::decodeHandShakeMessage(int id, CDatagramme *datagramme){

    QString addr = QString("%1.%2.%3.%4").
            arg(quint8(datagramme->getValue()->at(8))).
            arg(quint8(datagramme->getValue()->at(9))).
            arg(quint8(datagramme->getValue()->at(10))).
            arg(quint8(datagramme->getValue()->at(11)));

    int port = datagramme->getValue()->at(12)*100 + datagramme->getValue()->at(13);
    devices->append(id, port, addr, 0, 0, 1);

    igtClient *client = new igtClient(devices->getClientNumber()-1, this->oq, this->devices);
    client->connectBackRequest(addr, port);
}

//! ----------------------------------------------------------------------------------------
//!
//! \brief DatagrammeAnalyser::decodeCTImage
//! \param datagramme
//!
void DatagrammeAnalyser::decodeCTImage(CDatagramme *datagramme){

}


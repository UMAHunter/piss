#include "HandShakeMessage.h"

HandShakeMessage::HandShakeMessage()
{
}

HandShakeMessage::~HandShakeMessage(){

}

void HandShakeMessage::setDataType(unsigned char dataType){
    this->dataType = dataType;
}

void HandShakeMessage::setDeviceId(unsigned char deviceId){
    this->deviceId = deviceId;
}

void HandShakeMessage::setTimestamp(QString timestamp){
    this->timestamp = timestamp;
}

void HandShakeMessage::setDLC(int dlc){
    this->dlc = dlc;
}

void HandShakeMessage::setDeviceName(QString deviceName){
    this->deviceName = deviceName;
}

void HandShakeMessage::setLocalIP(QString addr){
    this->ip = addr;
}

void HandShakeMessage::setLocalPort(int port){
    this->port = port;
}

CDatagramme* HandShakeMessage::toCDatagram(){
    CDatagramme *datagrame;
    QByteArray buf;
    buf.resize(34);
    buf[0] = dataType;
    buf[1] = deviceId;
    buf.append(timestamp);//2~5
    buf[6] = (uchar)  (0x000000ff & dlc);
    buf[7] = (uchar) ((0x0000ff00 & dlc) >> 8);
    buf.append(deviceName);//8~27
    buf.append(ip.section('.', 0, 0).trimmed());
    buf.append(ip.section('.', 1, 1).trimmed());
    buf.append(ip.section('.', 2, 2).trimmed());
    buf.append(ip.section('.', 3, 3).trimmed());//28~31
    buf[32] = (uchar)  (0x000000ff & port);
    buf[33] = (uchar) ((0x0000ff00 & port) >> 8);
    datagrame->setValue(&buf);
    return datagrame;
}

void HandShakeMessage::decodeDatagram(CDatagramme *datagram){
    HandShakeMessage msg;
    msg.dataType = datagram->getDataType();
    msg.deviceId = datagram->getDeviceId();
    msg.timestamp = datagram->getTimestamp();
    msg.dlc = datagram->getDLC();
    //msg.deviceName = datagram->getValue();//to be reviewed
    msg.ip = QString("%1.%2.%3.%4").
        arg(quint8(datagram->getValue()->at(28))).
        arg(quint8(datagram->getValue()->at(29))).
        arg(quint8(datagram->getValue()->at(30))).
        arg(quint8(datagram->getValue()->at(31)));
    msg.port = datagram->getValue()->at(32)*100 + datagram->getValue()->at(33);
}

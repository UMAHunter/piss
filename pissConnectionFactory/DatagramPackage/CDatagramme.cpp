#include "CDatagramme.h"


/**
 * @brief CDatagramme::CDatagramme
 * @param value
 */
CDatagramme::CDatagramme(){

}

//!-------------------------------------------------------------
//!
//! \brief CDatagramme::~CDatagramme
//!
CDatagramme::~CDatagramme(){

}

//!-------------------------------------------------------------
//!
//! \brief CDatagramme::setValue
//! \param value
//!
void CDatagramme::setValue(QByteArray* value){
    this->value = value;
    this->totalLength = this->value->length();
}

//!-------------------------------------------------------------
//!
//! \brief CDatagramme::getValue
//! \return
//!
QByteArray* CDatagramme::getValue(){
    return this->value;
}

void CDatagramme::printSelf(){
    qDebug()<<this->totalLength<<":"<<this->value;

}

//!-------------------------------------------------------------
//!
//! \brief CDatagramme::getIdentifierByte
//! \return
//!
unsigned char CDatagramme::getDataType(){
    return this->value->at(0);
}

unsigned char CDatagramme::getDeviceId(){
    return this->value->at(1);
}

void CDatagramme::setTimestamp(qint32 time){
    (*this->value)[2] = time % int(pow(2, 8));
    (*this->value)[3] = time / int(pow(2, 8)) % int(pow(2, 8));
    (*this->value)[4] = time / int(pow(2, 16)) % int(pow(2,8));
    (*this->value)[5] = time / int(pow(2, 24)) % int(pow(2,8));
}

QString CDatagramme::getTimestamp()
{
    return QString("%1%2%3%4").arg(quint8(this->value->at(2))).arg(quint8(this->value->at(3))).arg(quint8(this->value->at(4))).arg(quint8(this->value->at(5)));
}

int CDatagramme::getDLC()
{
    return this->value->size() - 8;
}

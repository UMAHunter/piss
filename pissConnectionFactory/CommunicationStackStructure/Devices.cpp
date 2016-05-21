#include "Devices.h"


/**
 * @brief Devices::Devices
 */
Devices::Devices()
{
    this->deviceCount = 0;
    me = new Device();
    me->setIpAddress(ipDetect());
}

//!--------------------------------------------------------------------------------------------------------------------------------
//!
//! \brief Devices::getSelf
//! \return
//!
Device* Devices::getSelf(){
    return me;
}

//!--------------------------------------------------------------------------------------------------------------------------------
//!
//! \brief Devices::setMyListenPort
//! \param port
//!
void Devices::setMyListenPort(quint32 port){
    me->setClientlistenport(port);
}

//!--------------------------------------------------------------------------------------------------------------------------------
//!
//! \brief Devices::setSocketReceptionById
//! \param id
//! \param socketRec
//!
void Devices::setSocketReceptionById(int id, qintptr sr){
    this->incomingDevices.at(id)->setSocketrec(sr);
}

//!--------------------------------------------------------------------------------------------------------------------------------
//!
//! \brief pissNetworkEnvironment::addAClient
//!
int Devices::addClient(){
    Device* device = new Device();
    device->setId(this->deviceCount);
    mutex.lock();
    this->incomingDevices.append(device);
    mutex.unlock();
    this->deviceCount++;
    return (this->deviceCount-1);
}

//!--------------------------------------------------------------------------------------------------------------------------------
//!
//! \brief pissNetworkEnvironment::getClientNumber
//! \return
//!
int Devices::getClientNumber(){
    return this->deviceCount;
}

//!--------------------------------------------------------------------------------------------------------------------------------
//!
//! \brief pissNetworkEnvironment::selfDetectIP
//! \return
//!
QString Devices::ipDetect()
{
    foreach(const QHostAddress &address, QNetworkInterface::allAddresses())
    {
        if(address.protocol() == QAbstractSocket::IPv4Protocol && address != QHostAddress(QHostAddress::LocalHost))
            return address.toString();
    }
}

//!--------------------------------------------------------------------------------------------------------------------------------
//!
//! \brief pissNetworkEnvironment::init
//! \param Module
//! \param Port
//!
void Devices::append(QString deviceName, int Port)
{
    if(deviceName == "self")
    {
        Device* selfIpConfig = new Device();
        selfIpConfig->setIpAddress(this->ipDetect());
        selfIpConfig->setPortNumber(Port);
        selfIpConfig->setName(deviceName);
        selfIpConfig->setCode(0);
        mutex.lock();
        this->incomingDevices.append(selfIpConfig);
        mutex.unlock();
    }
}

//--------------------------------------------------------------------------------------------------------------------------------
//!
//! \brief pissNetworkEnvironment::append
//! \param ModuleNumber
//! \param Port
//!
void Devices::append(int id, int port){
    Device* device = new Device();
    device->setIpAddress(ipDetect());
    device->setPortNumber(port);
    device->setId(id);
    device->setSockettrans(0);
    device->setSocketrec(0);
    device->setCode(0);
    mutex.lock();
    this->incomingDevices.append(device);
    mutex.unlock();
}

//--------------------------------------------------------------------------------------------------------------------------------
//!
//! \brief pissNetworkEnvironment::init
//! \param ModuleName
//! \param Port
//! \param addr
//! \param Socketrec
//! \param Clientlistenport
//! \param Code
//!
void Devices::append(QString ModuleName,
                                    int Port,
                                    QString addr,
                                    int Socketrec,
                                    quint32 Clientlistenport,
                                    quint8 Code)
{
    mutex.lock();
    Device *missIpConfig = new Device();
    missIpConfig->setIpAddress(addr);
    missIpConfig->setPortNumber(Port);
    missIpConfig->setName(ModuleName);
    missIpConfig->setSocketrec(Socketrec);
    missIpConfig->setClientlistenport(Clientlistenport);
    missIpConfig->setCode(Code);
    this->incomingDevices.append(missIpConfig);
    mutex.unlock();
}

//--------------------------------------------------------------------------------------------------------------------------------
//!
//! \brief pissNetworkEnvironment::append
//! \param ModuleNumber
//! \param Port
//! \param addr
//! \param Socketrec
//! \param Clientlistenport
//! \param Code
//!
void Devices::append(int ModuleNumber,
                                    int Port,
                                    QString addr,
                                    int Socketrec,
                                    quint32 Clientlistenport,
                                    quint8 Code){
    mutex.lock();
    QHostAddress address(addr);
    Device *missIpConfig = new Device();
    missIpConfig->setIpAddress(addr);
    missIpConfig->setPortNumber(Port);
    missIpConfig->setId(ModuleNumber);
    missIpConfig->setSocketrec(Socketrec);
    missIpConfig->setClientlistenport(Clientlistenport);
    missIpConfig->setCode(Code);
    this->incomingDevices.append(missIpConfig);
    mutex.unlock();
}

//! --------------------------------------------------------------------------------------------------
//!
//! \brief Devices::setSocketTransById
//! \param id
//! \param Sockettrans
//!
void Devices::setSocketTransById(int id, qintptr st)
{
    mutex.lock();
    this->incomingDevices.at(id)->setSockettrans(st);
    mutex.unlock();
}

//! --------------------------------------------------------------------------------------------------
//!
//! \brief Devices::setIpAddressByModule
//! \param ModuleName
//! \param ip
//!
void Devices::setIpAddressById(int id, QString ip)
{
    mutex.lock();
    this->incomingDevices.at(id)->setIpAddress(ip);
    mutex.unlock();
}

void Devices::setClientlistenportById(int id, quint32 Clientlistenport)
{
    mutex.lock();
    this->incomingDevices.at(id)->setClientlistenport(Clientlistenport);
    mutex.unlock();
    emit update();
}

void Devices::setCodeByModule(QString ModuleName, bool Code)
{
    mutex.lock();
    for(unsigned char cpt = 0; cpt < this->incomingDevices.size(); cpt++)
    {
        if(this->incomingDevices.at(cpt)->getName() == ModuleName)
        {
            this->incomingDevices.at(cpt)->setCode(Code);
        }
    }
    mutex.unlock();
}




//--------------------------------------------------------------------------------------------------------------------------------
//!
//! \brief pissNetworkEnvironment::getIpAddressByModule
//! \param moduleName
//! \return
//!
QHostAddress Devices::getIpAddressByModule(QString ModuleName)
{
    QHostAddress ret;
    mutex.lock();
    for(unsigned char cpt = 0; cpt < this->incomingDevices.size(); cpt++)
    {
        if(this->incomingDevices.at(cpt)->getName() == ModuleName)
        {
            ret =  this->incomingDevices.at(cpt)->getIpAddress();
        }
    }
    mutex.unlock();
    return ret;
}

//--------------------------------------------------------------------------------------------------------------------------------
//!
//! \brief pissNetworkEnvironment::getIpAddressByModule
//! \param ModuleNumber
//! \return
//!
QHostAddress Devices::getIpAddressByModule(int ModuleNumber){
    QHostAddress ret;
    mutex.lock();
    for(unsigned char cpt = 0; cpt < this->incomingDevices.size(); cpt++)
    {
        if(this->incomingDevices.at(cpt)->getDeviceNumber() == ModuleNumber)
        {
            ret =  this->incomingDevices.at(cpt)->getIpAddress();
        }
    }
    mutex.unlock();
    return ret;
}

//--------------------------------------------------------------------------------------------------------------------------------
//!
//! \brief pissNetworkEnvironment::getPortByModule
//! \param moduleName
//! \return
//!
int Devices::getPortByModule(QString ModuleName)
{
    int ret = -1;
    mutex.lock();
    for(unsigned char cpt = 0; cpt < this->incomingDevices.size(); cpt++)
    {
        if(this->incomingDevices.at(cpt)->getName() == ModuleName)
        {
            ret = this->incomingDevices.at(cpt)->getPortNumber();
        }
    }
    mutex.unlock();
    return ret;
}

//--------------------------------------------------------------------------------------------------------------------------------
//!
//! \brief Devices::getMyListenPort
//! \return
//!
int Devices::getMyListenPort(){
    return this->me->getClientlistenport();
}

//--------------------------------------------------------------------------------------------------------------------------------
//!
//! \brief pissNetworkEnvironment::getPortByModule
//! \param ModuleNumber
//! \return
//!
int Devices::getPortByModule(int deviceNumber){
    int ret = -1;
    mutex.lock();
    for(unsigned char cpt = 0; cpt < this->incomingDevices.size(); cpt++)
    {
        if(this->incomingDevices.at(cpt)->getDeviceNumber() == deviceNumber)
        {
            ret = this->incomingDevices.at(cpt)->getPortNumber();
        }
    }
    mutex.unlock();
    return ret;
}

//--------------------------------------------------------------------------------------------------------------------------------
//!
//! \brief pissNetworkEnvironment::getSocketrecByModule
//! \param ModuleName
//! \return
//!
int Devices::getSocketrecByModule(QString ModuleName)
{
    //mutex.lock();
    for(unsigned char cpt = 0; cpt < this->incomingDevices.size(); cpt++)
    {
        if(this->incomingDevices.at(cpt)->getName() == ModuleName)
        {
            return this->incomingDevices.at(cpt)->getSocketrec();
        }
    }
    //mutex.unlock();
}

int Devices::getSockettransByModule(QString ModuleName)
{
    mutex.lock();
    for(unsigned char cpt = 0; cpt < this->incomingDevices.size(); cpt++)
    {
        if(this->incomingDevices.at(cpt)->getName() == ModuleName)
        {
            return this->incomingDevices.at(cpt)->getSockettrans();
        }
    }
    mutex.unlock();
}

int Devices::getSockettransByCode(quint8 Code)
{
    mutex.lock();
    for(unsigned char cpt = 0; cpt < this->incomingDevices.size(); cpt++)
    {
        if(this->incomingDevices.at(cpt)->getCode() == Code)
        {
            return this->incomingDevices.at(cpt)->getSockettrans();
        }
    }
    mutex.unlock();
}

quint32 Devices::getClientlistenportByModule(QString ModuleName)
{
    mutex.lock();
    for(unsigned char cpt = 0; cpt < this->incomingDevices.size(); cpt++)
    {
        if(this->incomingDevices.at(cpt)->getName() == ModuleName)
        {
            return this->incomingDevices.at(cpt)->getClientlistenport();
        }
    }
    mutex.unlock();
}

bool Devices::getCodeByModule(QString ModuleName)
{
    mutex.lock();
    for(unsigned char cpt = 0; cpt < this->incomingDevices.size(); cpt++)
    {
        if(this->incomingDevices.at(cpt)->getName() == ModuleName)
        {
            return this->incomingDevices.at(cpt)->getCode();
        }
    }
    mutex.unlock();
}

Device* Devices::getDeviceAt(int index){
    return incomingDevices.at(index);
}

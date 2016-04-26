#include "Devices.h"

Devices::Devices()
{
    this->deviceCount = 0;
}

//!--------------------------------------------------------------------------------------------------------------------------------
//!
//! \brief pissNetworkEnvironment::addAClient
//!
void Devices::addClient(){
    this->deviceCount++;
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
QHostAddress Devices::ipDetect()
{
    foreach(const QHostAddress &address, QNetworkInterface::allAddresses())
    {
        if(address.protocol() == QAbstractSocket::IPv4Protocol && address != QHostAddress(QHostAddress::LocalHost))
            return address;
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
        this->devices.append(selfIpConfig);
        mutex.unlock();
    }
}

//--------------------------------------------------------------------------------------------------------------------------------
//!
//! \brief pissNetworkEnvironment::append
//! \param ModuleNumber
//! \param Port
//!
void Devices::append(int ModuleNumber, int port){
    Device* device = new Device();
    device->setIpAddress(ipDetect());
    device->setPortNumber(port);
    device->setModuleNumber(ModuleNumber);
    device->setSockettrans(0);
    device->setSocketrec(0);
    device->setCode(0);
    mutex.lock();
    this->devices.append(device);
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
    QHostAddress address(addr);
    Device *missIpConfig = new Device();
    missIpConfig->setIpAddress(address);
    missIpConfig->setPortNumber(Port);
    missIpConfig->setName(ModuleName);
    missIpConfig->setSocketrec(Socketrec);
    missIpConfig->setClientlistenport(Clientlistenport);
    missIpConfig->setCode(Code);
    this->devices.append(missIpConfig);
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
    missIpConfig->setIpAddress(address);
    missIpConfig->setPortNumber(Port);
    missIpConfig->setModuleNumber(ModuleNumber);
    missIpConfig->setSocketrec(Socketrec);
    missIpConfig->setClientlistenport(Clientlistenport);
    missIpConfig->setCode(Code);
    this->devices.append(missIpConfig);
    mutex.unlock();

}


//--------------------------------------------------------------------------------------------------------------------------------
//!
//! \brief pissNetworkEnvironment::setModuleName
//! \param ModuleName
//!
void Devices::setModuleName(QString ModuleName)
{
    this->moduleName = ModuleName;
}

void Devices::setSockettransByModule(QString ModuleName, int Sockettrans)
{
    mutex.lock();
    for(unsigned char cpt = 0; cpt < this->devices.size(); cpt++)
    {
        if(this->devices.at(cpt)->getName() == ModuleName)
        {
            this->devices.at(cpt)->setSockettrans(Sockettrans);
        }
    }
    mutex.unlock();
}

void Devices::setIpAddressByModule(QString ModuleName, QHostAddress ip)
{
    mutex.lock();
    for(unsigned char cpt = 0; cpt < this->devices.size(); cpt++)
    {
        if(this->devices.at(cpt)->getName() == ModuleName)
        {
            this->devices.at(cpt)->setIpAddress(ip);
        }
    }
    mutex.unlock();
}

void Devices::setClientlistenportByModule(QString ModuleName, quint32 Clientlistenport)
{
    mutex.lock();
    for(unsigned char cpt = 0; cpt < this->devices.size(); cpt++)
    {
        if(this->devices.at(cpt)->getName() == ModuleName)
        {
            this->devices.at(cpt)->setClientlistenport(Clientlistenport);
        }
    }
    mutex.unlock();
}

void Devices::setCodeByModule(QString ModuleName, bool Code)
{
    mutex.lock();
    for(unsigned char cpt = 0; cpt < this->devices.size(); cpt++)
    {
        if(this->devices.at(cpt)->getName() == ModuleName)
        {
            this->devices.at(cpt)->setCode(Code);
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
    for(unsigned char cpt = 0; cpt < this->devices.size(); cpt++)
    {
        if(this->devices.at(cpt)->getName() == ModuleName)
        {
            ret =  this->devices.at(cpt)->getIpAddress();
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
    for(unsigned char cpt = 0; cpt < this->devices.size(); cpt++)
    {
        if(this->devices.at(cpt)->getDeviceNumber() == ModuleNumber)
        {
            ret =  this->devices.at(cpt)->getIpAddress();
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
    for(unsigned char cpt = 0; cpt < this->devices.size(); cpt++)
    {
        if(this->devices.at(cpt)->getName() == ModuleName)
        {
            ret = this->devices.at(cpt)->getPortNumber();
        }
    }
    mutex.unlock();
    return ret;
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
    for(unsigned char cpt = 0; cpt < this->devices.size(); cpt++)
    {
        if(this->devices.at(cpt)->getDeviceNumber() == deviceNumber)
        {
            ret = this->devices.at(cpt)->getPortNumber();
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
    for(unsigned char cpt = 0; cpt < this->devices.size(); cpt++)
    {
        if(this->devices.at(cpt)->getName() == ModuleName)
        {
            return this->devices.at(cpt)->getSocketrec();
        }
    }
    //mutex.unlock();
}

int Devices::getSockettransByModule(QString ModuleName)
{
    mutex.lock();
    for(unsigned char cpt = 0; cpt < this->devices.size(); cpt++)
    {
        if(this->devices.at(cpt)->getName() == ModuleName)
        {
            return this->devices.at(cpt)->getSockettrans();
        }
    }
    mutex.unlock();
}

int Devices::getSockettransByCode(quint8 Code)
{
    mutex.lock();
    for(unsigned char cpt = 0; cpt < this->devices.size(); cpt++)
    {
        if(this->devices.at(cpt)->getCode() == Code)
        {
            return this->devices.at(cpt)->getSockettrans();
        }
    }
    mutex.unlock();
}

quint32 Devices::getClientlistenportByModule(QString ModuleName)
{
    mutex.lock();
    for(unsigned char cpt = 0; cpt < this->devices.size(); cpt++)
    {
        if(this->devices.at(cpt)->getName() == ModuleName)
        {
            return this->devices.at(cpt)->getClientlistenport();
        }
    }
    mutex.unlock();
}

bool Devices::getCodeByModule(QString ModuleName)
{
    mutex.lock();
    for(unsigned char cpt = 0; cpt < this->devices.size(); cpt++)
    {
        if(this->devices.at(cpt)->getName() == ModuleName)
        {
            return this->devices.at(cpt)->getCode();
        }
    }
    mutex.unlock();
}

Device* Devices::getDeviceAt(int index){
    return devices.at(index);
}

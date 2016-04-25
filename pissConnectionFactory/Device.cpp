#include "Device.h"

Device::Device()
{

}

//--------------------------------------------------------------------------------------------------------------------------------
//!
//! \brief ModuleIpConfig::setModuleNumber
//! \param moduleNumber
//!
void Device::setModuleNumber(int moduleNumber){
    this->moduleNumber = moduleNumber;
    switch (moduleNumber){
        case PISS:
            setName("piss");
            break;
        case CCISS:
            setName("cciss");
            break;
        case MISS:
            setName("miss");
            break;
        default:
            break;
    }
}

//--------------------------------------------------------------------------------------------------------------------------------
//!
//! \brief ModuleIpConfig::getIpAddress
//! \return
//!
QHostAddress Device::getIpAddress()
{
    return this->addr;
}

//--------------------------------------------------------------------------------------------------------------------------------
//!
//! \brief ModuleIpConfig::getPort
//! \return
//!
int Device::getPortNumber()
{
    return this->portNumber;
}

//--------------------------------------------------------------------------------------------------------------------------------
//!
//! \brief ModuleIpConfig::getModuleNumber
//! \return
//!
int Device::getDeviceNumber(){
    return this->moduleNumber;
}

//--------------------------------------------------------------------------------------------------------------------------------
//!
//! \brief ModuleIpConfig::getName
//! \return
//!
QString Device::getName()
{
    return this->name;
}

//--------------------------------------------------------------------------------------------------------------------------------
//!
//! \brief ModuleIpConfig::getSocketrec
//! \return
//!
int Device::getSocketrec()
{
    return this->socketrec;
}

//--------------------------------------------------------------------------------------------------------------------------------
//!
//! \brief ModuleIpConfig::getSocketTrans
//! \return
//!
int Device::getSockettrans()
{
    return this->sockettrans;
}

//--------------------------------------------------------------------------------------------------------------------------------
//!
//! \brief ModuleIpConfig::getClientlistenport
//! \return
//!
quint32 Device::getClientlistenport()
{
    return this->clientlistenport;
}

//--------------------------------------------------------------------------------------------------------------------------------
//!
//! \brief ModuleIpConfig::getCode
//! \return
//!
bool Device::getCode()
{
    return this->code;
}



//--------------------------------------------------------------------------------------------------------------------------------
//!
//! \brief ModuleIpConfig::setIpAddress
//! \param Addr
//!
void Device::setIpAddress(QHostAddress Addr)
{
    this->addr = Addr;
}

//--------------------------------------------------------------------------------------------------------------------------------
//!
//! \brief ModuleIpConfig::setPort
//! \param Port
//!
void Device::setPortNumber(int p)
{
    this->portNumber = p;
}

//--------------------------------------------------------------------------------------------------------------------------------
//!
//! \brief ModuleIpConfig::setName
//! \param Name
//!
void Device::setName(QString Name)
{
    this->name = Name;
}

//--------------------------------------------------------------------------------------------------------------------------------
//!
//! \brief ModuleIpConfig::setSocketrec
//! \param Socketrec
//!
void Device::setSocketrec(int Socketrec)
{
    this->socketrec = Socketrec;
}

//--------------------------------------------------------------------------------------------------------------------------------
//!
//! \brief ModuleIpConfig::setSocketTrans
//! \param SocketTrans
//!
void Device::setSockettrans(int Sockettrans)
{
    this->sockettrans = Sockettrans;
}

//--------------------------------------------------------------------------------------------------------------------------------
//!
//! \brief ModuleIpConfig::setClientlistenport
//! \param Clientlistenport
//!
void Device::setClientlistenport(quint32 Clientlistenport)
{
    this->clientlistenport = Clientlistenport;
}

//--------------------------------------------------------------------------------------------------------------------------------
//!
//! \brief ModuleIpConfig::setCode
//! \param Code
//!
void Device::setCode(bool Code)
{
    this->code = Code;
}

#ifndef HANDSHAKEMESSAGE_H
#define HANDSHAKEMESSAGE_H

#include "CDatagramme.h"


/**
 * @brief The HandShakeMessage class
 */
class HandShakeMessage{

private:
    unsigned char dataType;
    unsigned char deviceId;
    QString timestamp;
    int dlc;
    QString deviceName;
    QString ip;
    int port;
public:
    CDatagramme* toCDatagram();
    void decodeDatagram(CDatagramme* datagram);

    void setDataType(unsigned char dataType);
    void setDeviceId(unsigned char deviceId);
    void setTimestamp(QString timestamp);
    void setDLC(int dlc);
    void setDeviceName(QString deviceName);
    void setLocalIP(QString addr);
    void setLocalPort(int port);
public:
    HandShakeMessage();
    ~HandShakeMessage();
};

#endif // HANDSHAKEMESSAGE_H

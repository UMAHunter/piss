#ifndef HANDSHAKEMESSAGE_H
#define HANDSHAKEMESSAGE_H

#include "CDatagramme.h"
#include "QString"
#include "QByteArray"

/**
 * @brief The HandShakeMessage class
 */
class HandShakeMessage{

public:
    QByteArray toCDatagram();
    void decodeDatagram(CDatagramme* datagram);

    void setDataType(unsigned char dataType);
    void setDeviceId(unsigned char deviceId);
    void setTimestamp(long long timestamp);
    void setDLC(int dlc);
    void setDeviceName(QString name);
    void setLocalIP(char a, char b, char c, char d);
    void setLocalPort(int port);

    unsigned char getDataType();
    unsigned char getDeviceId();
    unsigned long long getTimestamp();
    int getDLC();
    QString getDeviceName();
    QString getIp();
    int getPort();

private:
    unsigned char dataType;
    unsigned char deviceId;
    long long timestamp;
    int dlc;
    const char *deviceName;
    char ip[4];
    int port;

public:
    HandShakeMessage();
    ~HandShakeMessage();

};

#endif // HANDSHAKEMESSAGE_H


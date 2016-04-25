#ifndef MODULEIPCONFIG_H
#define MODULEIPCONFIG_H

#include<QHostAddress>


typedef enum {
    PISS = 0,
    MISS,
    CCISS
}ModuleCode;


class Device
{
public:
    Device();

    QHostAddress getIpAddress();
    int getPortNumber();
    QString getName();
    int getSocketrec();
    int getSockettrans();
    quint32 getClientlistenport();
    bool getCode();
    int getDeviceNumber();

    void setIpAddress(QHostAddress Addr);
    void setPortNumber(int p);
    void setName(QString Name);
    void setSocketrec(int Socketrec);
    void setSockettrans(int Sockettrans);
    void setClientlistenport(quint32 Clientlistenport);
    void setCode(bool Code);
    void setModuleNumber(int moduleNumber);

private:
    int moduleNumber;
    QHostAddress addr;
    int portNumber;
    QString name;
    qintptr socketrec;//接收到的socket
    qintptr sockettrans;//发起连接的socket
    quint32 clientlistenport;//对方监听的端口号
    bool code;//标识号
};

#endif // MODULEIPCONFIG_H

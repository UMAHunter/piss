#ifndef PISSNETWORKENVIRONMENT_H
#define PISSNETWORKENVIRONMENT_H

#include<QString>
#include<QHostAddress>
#include<QList>
#include<QNetworkInterface>
#include<QMutex>
#include"Device.h"


class Devices
{
public:
    Devices();
    void append(QString ModuleName, int Port);
    void append(int ModuleNumber, int Port);
    void append(QString ModuleName, int Port, QString addr, int Socketrec, quint32 Clientlistenport, quint8 Code);
    void append(int ModuleNumber, int Port, QString addr, int Socketrec, quint32 Clientlistenport, quint8 Code);

    QHostAddress ipDetect();

    void setModuleName(QString ModuleName);
    void setIpAddressByModule(QString ModuleName, QHostAddress ip);
    void setSockettransByModule(QString ModuleName, int Sockettrans);
    void setClientlistenportByModule(QString ModuleName, quint32 Clientlistenport);
    void setCodeByModule(QString ModuleName, bool Code);

    QHostAddress getIpAddressByModule(QString ModuleName);
    QHostAddress getIpAddressByModule(int ModuleNumber);

    int getPortByModule(QString ModuleName);
    int getPortByModule(int ModuleNumber);

    int getSocketrecByModule(QString ModuleName);
    int getSockettransByModule(QString ModuleName);
    int getSockettransByCode(quint8 Code);
    quint32 getClientlistenportByModule(QString ModuleName);
    bool getCodeByModule(QString ModuleName);

    void addClient();
    int getClientNumber();

    Device* getDeviceAt(int index);
private:
    QMutex mutex;
    int deviceCount;
    QString moduleName;
    QList <Device*> devices;
};

#endif // PISSNETWORKENVIRONMENT_H

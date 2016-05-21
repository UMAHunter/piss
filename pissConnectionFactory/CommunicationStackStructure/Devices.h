#ifndef PISSNETWORKENVIRONMENT_H
#define PISSNETWORKENVIRONMENT_H

#include<QString>
#include<QHostAddress>
#include<QList>
#include<QNetworkInterface>
#include<QMutex>
#include"Device.h"


/**
 * @brief The Devices class
 */
class Devices:public QObject
{
    Q_OBJECT
public:
    void append(QString ModuleName, int Port);
    void append(int ModuleNumber, int Port);
    void append(QString ModuleName, int Port, QString addr, int Socketrec, quint32 Clientlistenport, quint8 Code);
    void append(int ModuleNumber, int Port, QString addr, int Socketrec, quint32 Clientlistenport, quint8 Code);

    void setIpAddressById(int id, QString ip);
    void setSocketTransById(int id, qintptr st);
    void setSocketReceptionById(int id, qintptr sr);
    void setClientlistenportById(int id, quint32 Clientlistenport);
    void setCodeByModule(QString ModuleName, bool Code);

    QHostAddress getIpAddressByModule(QString ModuleName);
    QHostAddress getIpAddressByModule(int ModuleNumber);
    QString ipDetect();

    int getPortByModule(QString ModuleName);
    int getPortByModule(int ModuleNumber);

    int getSocketrecByModule(QString ModuleName);
    int getSockettransByModule(QString ModuleName);
    int getSockettransByCode(quint8 Code);
    quint32 getClientlistenportByModule(QString ModuleName);
    bool getCodeByModule(QString ModuleName);

    int addClient();
    int getClientNumber();

    Device* getDeviceAt(int index);

    Device* getSelf();
    void setMyListenPort(quint32 port);
    int getMyListenPort();

signals:
    void update();

private:
    QMutex mutex;

    int deviceCount;

    Device* me;

    QList <Device*> incomingDevices;

public:
    Devices();
};

#endif // PISSNETWORKENVIRONMENT_H

#ifndef DATAGRAMMEANALYSER_H
#define DATAGRAMMEANALYSER_H

#include <QHostAddress>
#include <QDateTime>
#include <QVector>
#include <QByteArray>
#include "InputQueue.h"
#include "OutputQueue.h"
#include "CDatagramme.h"
#include "Devices.h"
#include "pissTransmissionTask.h"
#include "GlobalTime.h"


//! Codes des erreurs remontees par les fonctions
typedef enum {
    HelloMessage = 0,
    HandShakeMessage,
    CTImage
}DatagrammeIdentifierCode;

/**
 * @brief The DatagrammeAnalyser class
 *
 */
class DatagrammeAnalyser
{
public:
    DatagrammeAnalyser(QVector <OutputQueue*> *oq, QVector <InputQueue*> *iq, Devices *environment, GlobalTime *globalTime);
    ~DatagrammeAnalyser();

    void encodage(QString modulename);
    void decodage(int id, CDatagramme *datagramme);

    void decodeHelloMessage(int id, CDatagramme *datagramme);
    void decodeHandShakeMessage(int id, CDatagramme *datagramme);
    void decodeCTImage(CDatagramme *datagramme);
    int getDatagrammeLength();
private:
    DatagrammeIdentifierCode identifierCode;

    QVector <InputQueue*> *iq;
    QVector <OutputQueue*> *oq;

    Devices *mNetworkEnvironment;
    GlobalTime *globalTime;
};

#endif // DATAGRAMMEANALYSER_H

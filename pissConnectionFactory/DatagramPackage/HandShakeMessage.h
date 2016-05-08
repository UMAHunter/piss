#ifndef HANDSHAKEMESSAGE_H
#define HANDSHAKEMESSAGE_H

#include "CDatagramme.h"


/**
 * @brief The HandShakeMessage class
 */
class HandShakeMessage{

private:


public:
    CDatagramme* toCDatagram();
    CDatagramme* decodeDatagram();

public:
    HandShakeMessage();
};

#endif // HANDSHAKEMESSAGE_H

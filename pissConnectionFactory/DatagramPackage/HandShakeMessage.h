#ifndef HANDSHAKEMESSAGE_H
#define HANDSHAKEMESSAGE_H

#include "CDatagramme.h"

class HandShakeMessage
{

private:


public:
    CDatagramme* toCDatagram();
    CDatagramme* decodeDatagram();

public:
    HandShakeMessage();
};

#endif // HANDSHAKEMESSAGE_H

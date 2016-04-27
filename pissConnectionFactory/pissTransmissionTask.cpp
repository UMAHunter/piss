#include "pissTransmissionTask.h"


pissTransmissionTask::pissTransmissionTask(int id, QVector<OutputQueue *> *oq, Devices* environment, QTcpSocket* socketTransmission){
    this->id = id;

    this->oq = oq;
    this->devices = environment;
    this->socketTransmission = socketTransmission;

    frameCounter = 0;
    transmissionTimer = new QTimer();

    this->connect(this->transmissionTimer, SIGNAL(timeout()), this, SLOT(transfer()));
}

pissTransmissionTask::~pissTransmissionTask(){

}

void pissTransmissionTask::launch(){
    this->transmissionTimer->start(20);
}

void pissTransmissionTask::transfer(){
    outputMutex.lock();
    if(oq->size() > 0){
        int length = oq->at(id)->getLength();
        if(length > 0)
        {
            this->socketTransmission->write(*(oq->at(id)->fetchFirstDatagramme()->getValue()));
            this->socketTransmission->waitForBytesWritten(-1);
            frameCounter ++;
        }
    }
    outputMutex.unlock();
}

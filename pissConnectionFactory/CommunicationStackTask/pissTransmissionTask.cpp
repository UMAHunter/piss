#include "pissTransmissionTask.h"


pissTransmissionTask::pissTransmissionTask(int id, QVector<OutputQueue *> *oq, Devices* environment, QTcpSocket* socketTransmission){
    this->id = id;
    this->oq = oq;
    qDebug()<<"pissTransmissionTask"<<oq;
    this->devices = environment;
    this->transmissionSocket = socketTransmission;

    frameCounter = 0;
    transmissionTimer = new QTimer();

    this->connect(this->transmissionTimer, SIGNAL(timeout()), this, SLOT(transfer()));
}

pissTransmissionTask::~pissTransmissionTask(){

}

void pissTransmissionTask::launch(){
    //this->transmissionTimer->start(20);
    this->start();
}

void pissTransmissionTask::run(){
    while(1){
        outputMutex.lock();
        if(oq->size() > 0){
            qDebug()<<"start transfer"<<id;
            if(oq->at(id)->getLength() > 0)
            {
                qDebug()<<id<<"trans"<<oq->at(id)->getLength()<<oq->at(id)->fetchFirstDatagramme();
                qDebug()<<oq->at(id)->fetchFirstDatagramme()->getValue();
                qDebug()<<"trans";
                this->transmissionSocket->write(*(oq->at(id)->fetchFirstDatagramme()->getValue()));
                qDebug()<<"pre"<<oq->at(id)->fetchFirstDatagramme()->getDataType();
                oq->at(id)->deleteFrontElement();
                this->transmissionSocket->waitForBytesWritten(-1);
                frameCounter ++;
            }
            else{
                qDebug()<<"no msg in the outputqueue"<<id;
            }
        }
        outputMutex.unlock();
        sleep(1);
    }
}

void pissTransmissionTask::transfer(){
    qDebug()<<"start transfer";
//    outputMutex.lock();
//    if(oq->size() > 0){
//        int length = oq->at(id)->getLength();
//        if(length > 0)
//        {
//            this->transmissionSocket->write(*(oq->at(id)->fetchFirstDatagramme()->getValue()));
//            oq->at(id)->deleteFrontElement();
//            this->transmissionSocket->waitForBytesWritten(-1);
//            frameCounter ++;
//        }
//    }
//    outputMutex.unlock();
}

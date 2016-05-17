#include "OutputQueue.h"

OutputQueue::OutputQueue()
{
}

OutputQueue::~OutputQueue()
{

}

void OutputQueue::append(CDatagramme *datagramme)
{
    oqMutex.lock();
    qDebug()<<"append"<<datagramme<<datagramme->getValue();
    outputqueue.append(datagramme);
    oqMutex.unlock();
}

void OutputQueue::clear(){
    oqMutex.lock();
    outputqueue.clear();
    oqMutex.unlock();
}

void OutputQueue::deleteFrontElement()
{
    oqMutex.lock();
    outputqueue.pop_front();
    oqMutex.unlock();
}

CDatagramme* OutputQueue::fetchFirstDatagramme()
{
    qDebug()<<"fetch"<<outputqueue.at(0)<<outputqueue.at(0)->getValue();
    CDatagramme *ret;
    oqMutex.lock();
    ret = outputqueue.at(0);
    oqMutex.unlock();
    return ret;
}

int OutputQueue::getLength(){
    int ret = 0;
    oqMutex.lock();
    ret = outputqueue.size();
    oqMutex.unlock();
    return ret;
}

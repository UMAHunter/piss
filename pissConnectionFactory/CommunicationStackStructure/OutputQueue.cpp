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

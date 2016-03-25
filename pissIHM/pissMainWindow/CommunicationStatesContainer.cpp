#include "CommunicationStatesContainer.h"

CommunicationStatesContainer::CommunicationStatesContainer(int width, int height): QFrame()
{
    setStyleSheet("background-color:skyblue");
    this->width = width;
    this->height = height;
    this->setFixedSize(this->width, this->height);

    this->initVariable();
    this->constructIHM();
    this->setConnections();
}

void CommunicationStatesContainer::initVariable(){

}

void CommunicationStatesContainer::constructIHM(){

}

void CommunicationStatesContainer::setConnections(){

}

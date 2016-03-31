#include "SystemComponentsContainer.h"

SystemComponentsContainer::SystemComponentsContainer(int width, int height) : QFrame()
{
    //setStyleSheet("background-color:cyan");
    this->width = width;
    this->height = height;

    this->setFixedSize(this->width, this->height);
}


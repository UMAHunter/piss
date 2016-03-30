#include "CommunicationStatesContainer.h"

CommunicationStatesContainer::CommunicationStatesContainer(int width, int height): QFrame()
{
    this->width = width;
    this->height = height;
    this->setFixedSize(this->width, this->height);

    this->initVariable();
    this->constructIHM();
    this->setConnections();
}

void CommunicationStatesContainer::initVariable(){

}

//! ---------------------------------------------------------------------------------------------------
//!
//! \brief CommunicationStatesContainer::constructIHM
//!
void CommunicationStatesContainer::constructIHM(){

    this->HardwareInformation = new QTableWidget(4, 4);
    this->HardwareInformation->setFixedSize(0.5*width, 0.3*height);
    QStringList hardwareHeader;
    hardwareHeader<<"ID"<<"Name"<<"Hardware IP"<<"Port";
    this->HardwareInformation->setHorizontalHeaderLabels(hardwareHeader);

    this->communicationFrameRateWindow = new PlottingBoard();
    this->communicationFrameRateWindow->setFixedSize(0.5*width, 0.3*height);

    this->communicationInformationWindow = new QWidget();
    this->communicationInformationWindowLayout = new QHBoxLayout(communicationInformationWindow);
    this->communicationInformationWindowLayout->addWidget(this->HardwareInformation);
    this->communicationInformationWindowLayout->addWidget(this->communicationFrameRateWindow);
    this->communicationInformationWindowLayout->setSpacing(0);
    this->communicationInformationWindowLayout->setMargin(0);

    this->TransmitBuffer = new QTableWidget(10, 5);
    this->TransmitBuffer->setFixedHeight(0.35*height);
    QStringList transmissionHeader;
    transmissionHeader<<"ID"<<"Timestamp"<<"DLC";
    this->TransmitBuffer->setHorizontalHeaderLabels(transmissionHeader);

    this->ReceiveBuffer = new QTableWidget(10, 5);
    this->ReceiveBuffer->setFixedHeight(0.35*height);
    this->ReceiveBuffer->setHorizontalHeaderLabels(transmissionHeader);

    this->CommunicationStatesContainerLayout = new QVBoxLayout(this);
    this->CommunicationStatesContainerLayout->addWidget(communicationInformationWindow);
    this->CommunicationStatesContainerLayout->addWidget(TransmitBuffer);
    this->CommunicationStatesContainerLayout->addWidget(ReceiveBuffer);
    this->CommunicationStatesContainerLayout->setSpacing(0);
    this->CommunicationStatesContainerLayout->setMargin(0);
}

//! ---------------------------------------------------------------------------------------------------
//!
//! \brief CommunicationStatesContainer::setConnections
//!
void CommunicationStatesContainer::setConnections(){

}

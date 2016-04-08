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

//! ---------------------------------------------------------------------------------------------------
//!
//! \brief CommunicationStatesContainer::initVariable
//!
void CommunicationStatesContainer::initVariable(){

    hardwareHeader<<"device"<<"address"<<"port"<<"transmission"<<"reception"<<"control";

    transmissionHeader<<"channel"<<"version"<<"type"<<"device"<<"timestamp"<<"dlc"<<"data0"<<"data1"<<"data2"<<"data3"<<"data4"<<"data5"<<"data6"<<"data7"<<"data8"<<"data9"<<"...";

    groupBoxStyleSheet = "QGroupBox {background-color: transparent;border: 1px solid beige;border-radius: 0px;margin-top: 1ex; /* leave space at the top for the title */}"
                         "QGroupBox::title {subcontrol-origin: margin;subcontrol-position: bottom right; /* position at the top center */padding: 0 3px;color: aliceblue}";
}

//! ---------------------------------------------------------------------------------------------------
//!
//! \brief CommunicationStatesContainer::constructIHM
//!
void CommunicationStatesContainer::constructIHM(){

    this->HardwareInformation = new QTableWidget(4, 6);
    this->HardwareInformation->setFixedSize(0.5*width, 0.3*height);
    this->HardwareInformation->setHorizontalHeaderLabels(hardwareHeader);
    this->HardwareInformation->verticalHeader()->setVisible(false);
    this->HardwareInformation->setStyleSheet("color: teal;background-color: rgba(0,0,0,0);border: 0px groove gray;gridline-color: lightYellow;");
    this->HardwareInformation->resizeColumnsToContents();

    this->communicationFrameRateWindow = new PlottingBoard();
    this->communicationFrameRateWindow->setFixedSize(0.5*width, 0.3*height);
    this->communicationFrameRateWindow->setWorkSpaceColor("aliceblue");

    this->communicationInformationWindow = new QWidget();
    this->communicationInformationWindowLayout = new QHBoxLayout(communicationInformationWindow);
    this->communicationInformationWindowLayout->addWidget(this->HardwareInformation);
    this->communicationInformationWindowLayout->addWidget(this->communicationFrameRateWindow);
    this->communicationInformationWindowLayout->setSpacing(0);
    this->communicationInformationWindowLayout->setMargin(0);

    transmissionBuffer = new QTreeWidget();
    transmissionBuffer->setStyleSheet("background-color:transparent;gridline-color: rgba(125, 125, 125, 125);color: rgb(255, 255, 255);");
    transmissionBuffer->setFixedHeight(0.3*height);
    transmissionBuffer->setColumnCount(17);
    transmissionBuffer->setHeaderLabels(transmissionHeader);//configurer les titres de chaque colone
    transmissionBuffer->header()->setStyleSheet("QHeaderView::section {background-color:transparent;color:beige; padding-left:4px; border: 1px solid #6c6c6c}");
    transmissionBuffer->setColumnWidth(0, 60);
    transmissionBuffer->setColumnWidth(1, 50);
    transmissionBuffer->setColumnWidth(2, 50);
    transmissionBuffer->setColumnWidth(3, 50);
    transmissionBuffer->setColumnWidth(4, 70);
    transmissionBuffer->setColumnWidth(5, 50);
    transmissionBuffer->setColumnWidth(6, 50);
    transmissionBuffer->setColumnWidth(7, 50);
    transmissionBuffer->setColumnWidth(8, 50);
    transmissionBuffer->setColumnWidth(9, 50);
    transmissionBuffer->setColumnWidth(10, 50);
    transmissionBuffer->setColumnWidth(11, 50);
    transmissionBuffer->setColumnWidth(12, 50);
    transmissionBuffer->setColumnWidth(13, 50);
    transmissionBuffer->setColumnWidth(14, 50);
    transmissionBuffer->setColumnWidth(15, 50);
    transmissionBuffer->setColumnWidth(16, 20);
    transmissionBuffer->setSelectionBehavior ( QAbstractItemView::SelectRows);

    receptionBuffer = new QTreeWidget();
    receptionBuffer->setStyleSheet("background-color:transparent;gridline-color: rgba(125, 125, 125, 125);color: rgb(255, 255, 255);");
    receptionBuffer->setFixedHeight(0.3*height);
    receptionBuffer->setColumnCount(17);
    receptionBuffer->setHeaderLabels(transmissionHeader);//configurer les titres de chaque colone
    receptionBuffer->header()->setStyleSheet("QHeaderView::section {background-color:transparent; color:beige; padding-left:4px; border: 1px solid #6c6c6c}");

    receptionBuffer->setColumnWidth(0, 60);
    receptionBuffer->setColumnWidth(1, 50);
    receptionBuffer->setColumnWidth(2, 50);
    receptionBuffer->setColumnWidth(3, 50);
    receptionBuffer->setColumnWidth(4, 70);
    receptionBuffer->setColumnWidth(5, 50);
    receptionBuffer->setColumnWidth(6, 50);
    receptionBuffer->setColumnWidth(7, 50);
    receptionBuffer->setColumnWidth(8, 50);
    receptionBuffer->setColumnWidth(9, 50);
    receptionBuffer->setColumnWidth(10, 50);
    receptionBuffer->setColumnWidth(11, 50);
    receptionBuffer->setColumnWidth(12, 50);
    receptionBuffer->setColumnWidth(13, 50);
    receptionBuffer->setColumnWidth(14, 50);
    receptionBuffer->setColumnWidth(15, 50);
    receptionBuffer->setColumnWidth(16, 20);
    receptionBuffer->setSelectionBehavior ( QAbstractItemView::SelectRows);

    transmissionArea = new QGroupBox();
    transmissionArea->setFixedHeight(0.35*height);
    transmissionArea->setTitle("transmission buffer");
    transmissionArea->setFont(QFont("Helvetica",12, QFont::AnyStyle, true));
    transmissionArea->setStyleSheet(groupBoxStyleSheet);
    transmissionAreaLayout = new QHBoxLayout(transmissionArea);
    transmissionAreaLayout->addWidget(transmissionBuffer);
    transmissionAreaLayout->setSpacing(0);
    transmissionAreaLayout->setMargin(0);

    receptionArea = new QGroupBox();
    receptionArea->setFixedHeight(0.35*height);
    receptionArea->setTitle("reception buffer");
    receptionArea->setFont(QFont("Helvetica",12, QFont::AnyStyle, true));
    receptionArea->setStyleSheet(groupBoxStyleSheet);
    receptionAreaLayout = new QHBoxLayout(receptionArea);
    receptionAreaLayout->addWidget(receptionBuffer);
    receptionAreaLayout->setSpacing(0);
    receptionAreaLayout->setMargin(0);

    this->CommunicationStatesContainerLayout = new QVBoxLayout(this);
    this->CommunicationStatesContainerLayout->addWidget(communicationInformationWindow);
    this->CommunicationStatesContainerLayout->addWidget(transmissionArea);
    this->CommunicationStatesContainerLayout->addWidget(receptionArea);
    this->CommunicationStatesContainerLayout->setSpacing(0);
    this->CommunicationStatesContainerLayout->setMargin(0);
}

//! ---------------------------------------------------------------------------------------------------
//!
//! \brief CommunicationStatesContainer::setConnections
//!
void CommunicationStatesContainer::setConnections(){

}

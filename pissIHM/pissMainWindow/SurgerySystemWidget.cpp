#include "SurgerySystemWidget.h"


SurgerySystemWidget::SurgerySystemWidget(int width, int height){

    this->width = width;
    this->height = height;

    this->initVariable();
    this->constructIHM();
    this->setConnections();
}

//! ---------------------------------------------------------------------------------------------
//!
//! \brief SurgerySystemWidget::initVariable
//!
void SurgerySystemWidget::initVariable(){

}

//! ---------------------------------------------------------------------------------------------
//!
//! \brief SurgerySystemWidget::constructIHM
//!
void SurgerySystemWidget::constructIHM(){
    //!-----------------------------------------------------------------------------------------
    surgerySystemControlBar = new QWidget();
    surgerySystemControlBar->setFixedHeight(this->height*0.05);
    surgerySystemControlBar->setStyleSheet("background-color:pink");

    //!-----------------------------------------------------------------------------------------
    //!
    //!  - luo jia ming
    //!
    systemComponentsContainer = new SystemComponentsContainer(width*0.5, this->height*0.95);

    //!  - fan de yuan
    communicationStatesContainer = new CommunicationStatesContainer(width*0.5, this->height*0.95);

    surgerySystemComponents = new QWidget();
    surgerySystemComponentsLayout = new QHBoxLayout(surgerySystemComponents);
    surgerySystemComponentsLayout->addWidget(systemComponentsContainer);
    surgerySystemComponentsLayout->addWidget(communicationStatesContainer);
    surgerySystemComponentsLayout->setSpacing(0);
    surgerySystemComponentsLayout->setMargin(0);


    myLayout = new QVBoxLayout(this);
    myLayout->addWidget(surgerySystemControlBar);
    myLayout->addWidget(surgerySystemComponents);
    myLayout->setSpacing(0);
    myLayout->setMargin(0);
}

//! ----------------------------------------------------------------------------------------------
//!
//! \brief SurgerySystemWidget::setConnections
//!
void SurgerySystemWidget::setConnections(){

}

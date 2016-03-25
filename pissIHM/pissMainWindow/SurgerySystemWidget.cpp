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
    surgerySystemComponents = new QWidget();

    systemComponentsContainer = new QFrame();
    systemComponentsContainer->setFixedWidth(width*0.5);
    systemComponentsContainer->setStyleSheet("background-color:cyan");

    communicationStatesContainer = new QFrame();
    communicationStatesContainer->setStyleSheet("background-color:skyblue");

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

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

    systemComponentsContainer = new QFrame();
    systemComponentsContainer->setFixedHeight(height*0.5);
    systemComponentsContainer->setStyleSheet("background-color:cyan");

    communicationStatesContainer = new QFrame();
    communicationStatesContainer->setStyleSheet("background-color:skyblue");


    surgerySystemWidgetLayout = new QVBoxLayout(this);
    surgerySystemWidgetLayout->addWidget(systemComponentsContainer);
    surgerySystemWidgetLayout->addWidget(communicationStatesContainer);
    surgerySystemWidgetLayout->setSpacing(0);
    surgerySystemWidgetLayout->setMargin(0);
}

//! ----------------------------------------------------------------------------------------------
//!
//! \brief SurgerySystemWidget::setConnections
//!
void SurgerySystemWidget::setConnections(){

}

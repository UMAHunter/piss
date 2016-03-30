#include "SurgerySystemWidget.h"


SurgerySystemWidget::SurgerySystemWidget(int width,
                                         int height,
                                         SystemDispatcher* systemDispatcher,
                                         AlgorithmTestPlatform* algorithmTestPlatform){

    this->width = width;
    this->height = height;
    this->systemDispatcher = systemDispatcher;
    this->algorithmTestPlatform = algorithmTestPlatform;

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
    startServerButton = new QPushButton();
    startServerButton->setIcon(QIcon(":/images/start.png"));
    startServerButton->setIconSize(QSize(this->width*0.025, this->height*0.04));
    startServerButton->setFixedSize(this->width*0.03, this->height*0.05);
    startServerButton->setFlat(true);

    stopServerButton = new QPushButton();
    stopServerButton->setIcon(QIcon(":/images/stop.png"));
    stopServerButton->setIconSize(QSize(this->width*0.025, this->height*0.04));
    stopServerButton->setFixedSize(this->width*0.03, this->height*0.05);
    stopServerButton->setFlat(true);

    surgerySystemControlBarItem = new QSpacerItem(20, 20, QSizePolicy::Expanding, QSizePolicy::Expanding);

    surgerySystemControlBar = new QWidget();
    surgerySystemControlBar->setFixedHeight(this->height*0.05);
    //surgerySystemControlBar->setStyleSheet("background-color:pink");
    surgerySystemControlBarLayout = new QHBoxLayout(surgerySystemControlBar);
    surgerySystemControlBarLayout->addWidget(startServerButton);
    surgerySystemControlBarLayout->addWidget(stopServerButton);
    surgerySystemControlBarLayout->addItem(surgerySystemControlBarItem);
    surgerySystemControlBarLayout->setSpacing(0);
    surgerySystemControlBarLayout->setMargin(0);

    //!----------------------------------------------------------------------------------------------
    //!
    //!  - luo jia ming
    //!
    systemComponentsContainer = new SystemComponentsContainer(width*0.5, this->height*0.95);

    //!----------------------------------------------------------------------------------------------
    //!
    //!  - fan de yuan
    //!
    communicationStatesContainer = new CommunicationStatesContainer(width*0.5, this->height*0.95);

    surgerySystemComponents = new QWidget();
    surgerySystemComponentsLayout = new QHBoxLayout(surgerySystemComponents);
    surgerySystemComponentsLayout->addWidget(communicationStatesContainer);
    surgerySystemComponentsLayout->addWidget(systemComponentsContainer);
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
    this->connect(startServerButton, SIGNAL(clicked()), this, SLOT(onStartServerButtonClicked()));
    this->connect(stopServerButton, SIGNAL(clicked()), this, SLOT(onStopServerButtonClicked()));
}

//! ----------------------------------------------------------------------------------------------
//!
//! \brief SurgerySystemWidget::closeSystem
//!
void SurgerySystemWidget::closeSystem(){
    onStopServerButtonClicked();
}

//! ----------------------------------------------------------------------------------------------
//!
//! \brief SurgerySystemWidget::onStopServerButtonClicked
//!
void SurgerySystemWidget::onStopServerButtonClicked(){
    bool ret = this->systemDispatcher->stopPissServer();
    if(ret){
        this->algorithmTestPlatform->setSystemStatus("platform server closed");
    }
    else{
        this->algorithmTestPlatform->setSystemStatus("please don't click the stop button when nothing happened");
    }
}

//! ----------------------------------------------------------------------------------------------
//!
//! \brief SurgerySystemWidget::onStartServerButtonClicked
//!
void SurgerySystemWidget::onStartServerButtonClicked(){
    bool ret = this->systemDispatcher->startPissServer();
    if(ret){
        this->algorithmTestPlatform->setSystemStatus("platform server started");
    }
    else{
        this->algorithmTestPlatform->setSystemStatus("platform server can't be started");
    }
}

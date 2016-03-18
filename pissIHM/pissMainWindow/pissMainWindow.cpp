#include "pissMainWindow.h"
#include "vtkImageData.h"


/**
 * @brief pissMainWindow::pissMainWindow
 * @param dispatcher
 */
pissMainWindow::pissMainWindow(SystemDispatcher* dispatcher): QWidget(){

    this->systemDispatcher = dispatcher;

    this->initVariable();
    this->constructIHM();
    this->globalBackgroundColorSetting();
    this->setConnections();
    this->drawBackground();
    this->onPatientsWidgetOptionReleased();
}

//!---------------------------------------------------------------------------------------
//!
//! \brief IgssMainWindow::initVariable
//!
void pissMainWindow::initVariable(){

    //! -------------------------------------------------------
    //! Faire la decoration de l'IHM
    //! -------------------------------------------------------
    this->setWindowFlags(Qt::FramelessWindowHint | Qt::WindowSystemMenuHint);
    this->setWindowOpacity(1);
    this->setMouseTracking(true);
    this->setAutoFillBackground(true);

    //! -------------------------------------------------------
    //! Des variable utile pour manipuler l'IHM
    //! -------------------------------------------------------
    this->buttonGaucheDuSourisClique = false;
    this->flag = 0;
    this->englishCaracterStyle = new QFont("Helvetica", 8, QFont::AnyStyle, true);
    this->globalBackgroundColor = "aliceBlue";

    //! -------------------------------------------------------
    //! Des procedure afin de recuperer les tailles des ¨¦crans;
    //! -------------------------------------------------------
    this->desktop = QApplication::desktop();
    this->screen_count = desktop->screenCount();
    this->primary_screen = desktop->primaryScreen();
    this->screen = new Screen[screen_count];
    for(unsigned char i = 0; i < screen_count; i++){
        screen[i].screenIndex = primary_screen + i;
        screen[i].rect = desktop->screenGeometry(primary_screen + i);
    }

    primary_screen_width = screen[0].rect.width();
    primary_screen_height = screen[0].rect.height();


    //!----------------------------------------------------------------------------------------------------
    //! status bar area
    //!----------------------------------------------------------------------------------------------------
    this->algorithmTestPlatform = new AlgorithmTestPlatform(this->systemDispatcher,
                                                            this->primary_screen_width,
                                                            this->primary_screen_height);

    this->patientInformationWidget = new PatientInformationWidget();

    this->surgeryTimer = new QTime();

    if(this->screen_count == 3){
        this->surgeryPlanWindow = new SurgeryPlanWindow(screen[1].rect,  this->surgeryTimer, this->systemDispatcher, this->algorithmTestPlatform);
        this->guidewareTrackingWindow = new GuidewareTrackingWindow(screen[2].rect, this->systemDispatcher);
        this->controlConsoleWindow = new ControlConsoleWindow(screen[1].rect,  this->surgeryTimer, this->systemDispatcher, this->algorithmTestPlatform);
        this->connect(this->controlConsoleWindow, SIGNAL(missionAccomplishiment()), this, SLOT(surgeryTerminated()));
    }

    systemOptionWindow = new SystemOptions();

}

//!---------------------------------------------------------------------------------------
//!
//! \brief IgssMainWindow::getAlgorithmTestPlatform
//! \return
//!
AlgorithmTestPlatform* pissMainWindow::getAlgorithmTestPlatform(){
    return this->algorithmTestPlatform;
}

//! ---------------------------------------------------------------------------------------
//!
//! \brief pissMainWindow::globalBackgroundColorSetting
//!
void pissMainWindow::globalBackgroundColorSetting(){
    configurationBoard->setStyleSheet("background-color:"+this->globalBackgroundColor);
    controlBoard->setStyleSheet("background-color:"+this->globalBackgroundColor);
    this->algorithmTestPlatform->setBackgroundColor(this->globalBackgroundColor);
}

//!---------------------------------------------------------------------------------------
//!
//! \brief IgssMainWindow::constructIHM
//!
void pissMainWindow::constructIHM(){

    //!------------------------------------------------------------------------------------------
    //! configurationBoard:
    //!------------------------------------------------------------------------------------------
    configurationBoard = new QWidget();
    configurationBoard->setFixedWidth(this->primary_screen_width*0.13);


    //!----------------------------------------------------------------------------------------------------------------------------
    //! le page pour visualiser les informations des maladies, aussi pour choisir le bonne personne qui doit commencer le th¨¦rapy
    //!----------------------------------------------------------------------------------------------------------------------------
    patientsWidget = new PatientsWidget(this->screen_count,
                                        this->systemDispatcher,
                                        this->algorithmTestPlatform,
                                        this->patientInformationWidget,
                                        this->surgeryTimer,
                                        this->englishCaracterStyle,
                                        this->primary_screen_width,
                                        this->primary_screen_height);

    if(this->screen_count == 3){
        this->patientsWidget->setSurgeryPlanWindow(this->surgeryPlanWindow);
        this->patientsWidget->setGuidewareTrackingWindow(this->guidewareTrackingWindow);
        this->patientsWidget->setControlConsoleWindow(this->controlConsoleWindow);
        this->patientsWidget->setParent(this);
    }

    //!----------------------------------------------------------------------------------------------------------------------------
    //! surveillance sur les ¨¦tats du system
    //!----------------------------------------------------------------------------------------------------------------------------
    surgerySystemWidget = new SurgerySystemWidget(primary_screen_width*0.846,primary_screen_height*0.79);

    //!----------------------------------------------------------------------------------------------------------------------------
    //! historique
    //!----------------------------------------------------------------------------------------------------------------------------
    replaysWidget = new ReplaysWidget();
    replaysWidget->setStyleSheet("background-color:red");

    patientsWidgetOption = new CPushButton();
    patientsWidgetOption->setText("Patients");
    patientsWidgetOption->setFixedSize(primary_screen_width*0.2, primary_screen_height*0.03);
    patientsWidgetOption->setFixedWidth(primary_screen_width*0.2);
    patientsWidgetOption->setStyleSheet( "border: 1px solid gainsboro;  border-radius: 0px; background-color: transparent;  min-width: 0px; color: gainsboro");
    patientsWidgetOption->setFlat(true);
    patientsWidgetOption->setFont(QFont("Segoe UI",12, QFont::AnyStyle, true));

    systemWidgetOption = new CPushButton();
    systemWidgetOption->setText("System");
    systemWidgetOption->setFixedSize(primary_screen_width*0.2, primary_screen_height*0.03);
    systemWidgetOption->setFixedWidth(primary_screen_width*0.2);
    systemWidgetOption->setStyleSheet( "border: 1px solid gainsboro;  border-radius: 0px; background-color: transparent;  min-width: 0px; color: gainsboro");
    systemWidgetOption->setFlat(true);
    systemWidgetOption->setFont(QFont("Segoe UI",12, QFont::AnyStyle, true));

    historyWidgetOption = new CPushButton();
    historyWidgetOption->setText("History");
    historyWidgetOption->setFixedSize(primary_screen_width*0.2, primary_screen_height*0.03);
    historyWidgetOption->setFixedWidth(primary_screen_width*0.2);
    historyWidgetOption->setStyleSheet( "border: 1px solid gainsboro;  border-radius: 0px; background-color: transparent;  min-width: 0px; color: gainsboro");
    historyWidgetOption->setFlat(true);
    historyWidgetOption->setFont(QFont("Segoe UI",12, QFont::AnyStyle, true));

    appIndicationLabel = new QLabel();
    appIndicationLabel->setFixedWidth(primary_screen_width*0.246);

    widgetOptionContainer = new QFrame();
    widgetOptionContainer->setStyleSheet("background-color: rgb(58, 89, 92)");
    widgetOptionContainer->setFixedHeight(primary_screen_height*0.03);
    widgetOptionContainerLayout = new QHBoxLayout(widgetOptionContainer);
    widgetOptionContainerLayout->addWidget(patientsWidgetOption);
    widgetOptionContainerLayout->addWidget(systemWidgetOption);
    widgetOptionContainerLayout->addWidget(historyWidgetOption);
    widgetOptionContainerLayout->addWidget(appIndicationLabel);
    widgetOptionContainerLayout->setSpacing(0);
    widgetOptionContainerLayout->setMargin(0);

    widgetsContainer = new QWidget();
    widgetsContainer->setFixedHeight(primary_screen_height*0.79);
    widgetsContainerLayout = new QHBoxLayout(widgetsContainer);
    widgetsContainerLayout->addWidget(patientsWidget);
    widgetsContainerLayout->addWidget(surgerySystemWidget);
    widgetsContainerLayout->addWidget(replaysWidget);
    widgetsContainerLayout->setSpacing(0);
    widgetsContainerLayout->setMargin(0);

    surgerySystemWidget->close();
    replaysWidget->close();

    systemInformationBoardWidget = new QWidget();
    systemInformationBoardWidgetLayout = new QVBoxLayout(systemInformationBoardWidget);
    systemInformationBoardWidgetLayout->addWidget(widgetOptionContainer);
    systemInformationBoardWidgetLayout->addWidget(widgetsContainer);
    systemInformationBoardWidgetLayout->setSpacing(0);
    systemInformationBoardWidgetLayout->setMargin(0);

    //!------------------------------------------------------------------------------------------
    //! controlBoard:
    //!------------------------------------------------------------------------------------------
    closeButton = new QPushButton();
    closeButton->setIcon(QIcon(":/images/close.png"));
    closeButton->setIconSize(QSize(this->primary_screen_width*0.019,this->primary_screen_width*0.019));
    closeButton->setStyleSheet("background-color:transparent");
    closeButton->setFixedSize(this->primary_screen_width*0.023, this->primary_screen_width*0.023);

    systemConfigurationButton = new QPushButton();
    systemConfigurationButton->setIcon(QIcon(":/images/system_configuration.png"));
    systemConfigurationButton->setIconSize(QSize(this->primary_screen_width*0.019,this->primary_screen_width*0.019));
    systemConfigurationButton->setStyleSheet("background-color:transparent");
    systemConfigurationButton->setFixedSize(this->primary_screen_width*0.023, this->primary_screen_width*0.023);

    controlAreaItem = new QSpacerItem(20, 20, QSizePolicy::Expanding, QSizePolicy::Expanding);

    controlBoard = new QWidget();

    controlBoard->setFixedWidth(this->primary_screen_width*0.024);
    controlBoardLayout = new QVBoxLayout(controlBoard);
    controlBoardLayout->addWidget(closeButton);
    controlBoardLayout->addWidget(systemConfigurationButton);
    controlBoardLayout->addItem(controlAreaItem);
    controlBoardLayout->setSpacing(0);
    controlBoardLayout->setMargin(0);

    //!----------------------------------------------------------------------------------------------------
    //! main platform
    //!----------------------------------------------------------------------------------------------------
    mainPlatform = new QWidget();
    mainPlatformLayout = new QHBoxLayout(mainPlatform);
    mainPlatformLayout->addWidget(configurationBoard);
    mainPlatformLayout->addWidget(systemInformationBoardWidget);
    mainPlatformLayout->addWidget(controlBoard);
    mainPlatformLayout->setSpacing(0);
    mainPlatformLayout->setMargin(0);

    //!----------------------------------------------------------------------------------------------------
    //! main window
    //!----------------------------------------------------------------------------------------------------
    igssMainWindowLayout =  new QVBoxLayout(this);
    igssMainWindowLayout->addWidget(mainPlatform);
    igssMainWindowLayout->addWidget(algorithmTestPlatform);
    igssMainWindowLayout->setSpacing(1);
    igssMainWindowLayout->setMargin(0);
}

//! ---------------------------------------------------------------------------------------
//!
//! \brief IgssMainWindow::findPatientExisted
//!
void pissMainWindow::findPatientExisted(){
   patientsWidget->findPatientExisted();
}

//! -----------------------------------------------------------------------------------------
//!
//! \brief AnalyserMainWindow::drawBackground
//!
void pissMainWindow::drawBackground(){
    this->setStyleSheet("background:rgb(58, 89, 92);");

//    pixmap = new QPixmap(":/images/background.png");
//    QPalette p =  this->palette();

//    p.setBrush(QPalette::Background, QBrush(pixmap->scaled(QSize(this->primary_screen_width, this->primary_screen_height), Qt::IgnoreAspectRatio, Qt::SmoothTransformation)));

//    this->setPalette(p);
//    this->setMask(pixmap->mask());
}

//!------------------------------------------------------------------------------------------------------------------------------------------------
//!
//! \brief IgssMainWindow::setConnectios
//!
void pissMainWindow::setConnections(){

    this->connect(this->patientsWidget, SIGNAL(surgeryLaunchButtonCicked()), this, SLOT(close()));

    this->connect(closeButton, SIGNAL(clicked()), this, SLOT(closeSystem()));
    this->connect(systemConfigurationButton, SIGNAL(clicked()), this, SLOT(configurerLeSysteme()));

    this->connect(this->patientsWidgetOption, SIGNAL(mouseHover()), this, SLOT(onPatientsWidgetOptionHovered()));
    this->connect(this->patientsWidgetOption, SIGNAL(mouseLeftButtonClicked()), this, SLOT(onPatientsWidgetOptionClicked()));
    this->connect(this->patientsWidgetOption, SIGNAL(mouseLeftButtonReleased()), this, SLOT(onPatientsWidgetOptionReleased()));
    this->connect(this->patientsWidgetOption, SIGNAL(mouseLeaved()), this, SLOT(onPatientsWidgetOptionLeaved()));

    this->connect(this->systemWidgetOption, SIGNAL(mouseHover()), this, SLOT(onSystemWidgetOptionHovered()));
    this->connect(this->systemWidgetOption, SIGNAL(mouseLeftButtonClicked()), this, SLOT(onSystemWidgetOptionClicked()));
    this->connect(this->systemWidgetOption, SIGNAL(mouseLeftButtonReleased()), this, SLOT(onSystemWidgetOptionReleased()));
    this->connect(this->systemWidgetOption, SIGNAL(mouseLeaved()), this, SLOT(onSystemWidgetOptionLeaved()));

    this->connect(this->historyWidgetOption, SIGNAL(mouseHover()), this, SLOT(onHistoryWidgetOptionHovered()));
    this->connect(this->historyWidgetOption, SIGNAL(mouseLeftButtonClicked()), this, SLOT(onHistoryWidgetOptionClicked()));
    this->connect(this->historyWidgetOption, SIGNAL(mouseLeftButtonReleased()), this, SLOT(onHistoryWidgetOptionReleased()));
    this->connect(this->historyWidgetOption, SIGNAL(mouseLeaved()), this, SLOT(onHistoryWidgetOptionLeaved()));

    this->connect(this->systemOptionWindow, SIGNAL(confirm()), this, SLOT(updateIHM()));

}

//!------------------------------------------------------------------------------------------------------------------------------------------------
//!
//! \brief pissMainWindow::updateIHM
//!
void pissMainWindow::updateIHM(){

    this->globalBackgroundColor = this->systemOptionWindow->getSystemGlobalBackgroundColor();

    globalBackgroundColorSetting();

    if(mainOptionStates.historyWidgetOptionState){
        this->onHistoryWidgetOptionReleased();
    }
    else if(mainOptionStates.patientsWidgetOptionState){
        this->onPatientsWidgetOptionReleased();
    }
    else if(mainOptionStates.systemWidgetOptionState){
        this->onSystemWidgetOptionReleased();
    }

}

//! ---------------------------------------------------------------------------------------------------------------------------------------------
//!
//! \brief pissMainWindow::configurerLeSysteme
//!
void pissMainWindow::configurerLeSysteme(){
    systemOptionWindow->show();
}

//!-------------------------------------------------------------------------------------------------------------------------------------------------
//!
//! \brief pissMainWindow::surgeryTerminated
//!
void pissMainWindow::surgeryTerminated(){

    qDebug()<<"surgeryTerminated";

    this->controlConsoleWindow->close();

    this->patientsWidget->terminateSurgery();

    this->showFullScreen();
}

//!----------------------------------------------------------------------------------------
//!
//! \brief IgssMainWindow::initVisualizationComponents
//!
void pissMainWindow::initVisualizationComponents(){
    volumeMapper = vtkVolumeRayCastMapper::New();
    compositeFunction = vtkVolumeRayCastCompositeFunction::New();
    volume = vtkVolume::New();
    renderWindow = vtkSmartPointer<vtkRenderWindow>::New();
    renderer = vtkSmartPointer<vtkRenderer>::New();
}

//!----------------------------------------------------------------------------------------
//!
//! \brief IgssMainWindow::display
//!
void pissMainWindow::display(){
    this->showFullScreen();
}

//!----------------------------------------------------------------------------------------
//!
//! \brief IgssMainWindow::setSystemDispatecher
//! \param dispatcher
//!
void pissMainWindow::setSystemDispatcher(SystemDispatcher* dispatcher){
    this->systemDispatcher = dispatcher;
}

//!----------------------------------------------------------------------------------------
//!
//! \brief IgssMainWindow::displayMraImage
//! \param input
//!
void pissMainWindow::displayMraImage(vtkImageData* input){
    this->volumeMapper->SetVolumeRayCastFunction(compositeFunction);
    this->volumeMapper->SetInputData(input);
    this->volume->SetMapper(volumeMapper);
    this->renderer->AddVolume(volume);
    this->renderer->SetBackground(0.1, 0.21, 0.31);
    this->renderWindow->AddRenderer(renderer);
    this->renderer->ResetCamera();
    this->mraImageDisplayWindow->SetRenderWindow(this->renderWindow);
}

//!----------------------------------------------------------------------------------------
//!
//! \brief Widget::readImageFileFrom
//! \param path
//!
void pissMainWindow::readImageFileFrom(QString path){
    mhdImagePath = path;
    mraImage = new IgssImage();
    mhdFileReader = new MRAFileReader();
    mhdFileReader->doParseMHDFileToIgssImage(mhdImagePath ,mraImage);

}

//!----------------------------------------------------------------------------------------
//!
//! \brief Widget::readImageFromVtkConvert
//!
void pissMainWindow::readImageFromVtkConvert()
{
    igssImage = new IgssImage();
    vtkImage = vtkImageData::New();
    vtkImage->SetDimensions(25,25,25);
    vtkImage->SetSpacing(1.0,1.0,1.0);
    vtkImage->SetOrigin(0.0,0.0,0.0);
    vtkImage->AllocateScalars(VTK_UNSIGNED_SHORT,1);
    unsigned short *ptr = (unsigned short*)vtkImage->GetScalarPointer();
    for(long i=0;i<25*25*25;i++)
    {
        *ptr++ = i;
    }
    igssVtkImageConverter = new IgssVtkImageConverter();
    igssVtkImageConverter->VtkToIgss(vtkImage,igssImage);
}

//!----------------------------------------------------------------------------------------
//!
//! \brief IgssMainWindow::closeSystem
//!
void pissMainWindow::closeSystem(){

    if (!(QMessageBox::information(this,tr("Igss Control View"),tr("Do you really want to log out Igss Control View?"),tr("Yes"),tr("No")))){
        this->close();
        this->guidewareTrackingWindow->close();
        this->surgeryPlanWindow->close();
        systemOptionWindow->close();
    }
}

//--------------------------------------------------------------------------------------------------------------------------------
//!
//! \brief pissMainWindow::onPatientsWidgetOptionHovered
//!
void pissMainWindow::onPatientsWidgetOptionHovered(){
    if(!mainOptionStates.patientsWidgetOptionState){
        patientsWidgetOption->setStyleSheet( "border-bottom: 1px solid orange;  border-radius: 0px; background-color: gainsboro;  min-width: 0px; color:"+this->globalBackgroundColor );
    }
}

//--------------------------------------------------------------------------------------------------------------------------------
//!
//! \brief pissMainWindow::onPatientsWidgetOptionClicked
//!
void pissMainWindow::onPatientsWidgetOptionClicked(){
    patientsWidgetOption->setStyleSheet( "border-bottom: 1px solid orange;  border-radius: 0px; background-color: transparent;  min-width: 0px; color:"+this->globalBackgroundColor );
}

//--------------------------------------------------------------------------------------------------------------------------------
//!
//! \brief pissMainWindow::onPatientsWidgetOptionReleased
//!
void pissMainWindow::onPatientsWidgetOptionReleased(){
    patientsWidgetOption->setStyleSheet( "border-bottom: 1px solid orange;  border-radius: 0px; background-color: rgb(58, 89, 92);  min-width: 0px; color:" + this->globalBackgroundColor );
    systemWidgetOption->setStyleSheet( "border-bottom: 1px solid orange;  border-radius: 0px; background-color:"+this->globalBackgroundColor+";  min-width: 0px; color: rgb(58, 89, 92)  "  );
    historyWidgetOption->setStyleSheet( "border-bottom: 1px solid orange;  border-radius: 0px; background-color: "+this->globalBackgroundColor+";  min-width: 0px; color: rgb(58, 89, 92)  "  );

    patientsWidgetOption->setFont(QFont("Segoe UI", 12, QFont::DemiBold, true));
    systemWidgetOption->setFont(QFont("Segoe UI", 12, QFont::AnyStyle, true));
    historyWidgetOption->setFont(QFont("Segoe UI", 12, QFont::AnyStyle, true));

    mainOptionStates.patientsWidgetOptionState = true;
    mainOptionStates.systemWidgetOptionState = false;
    mainOptionStates.historyWidgetOptionState = false;

    patientsWidget->show();
    surgerySystemWidget->close();
    replaysWidget->close();
}

//--------------------------------------------------------------------------------------------------------------------------------
//!
//! \brief pissMainWindow::onPatientsWidgetOptionLeaved
//!
void pissMainWindow::onPatientsWidgetOptionLeaved(){
    if(mainOptionStates.patientsWidgetOptionState){
        patientsWidgetOption->setStyleSheet( "border-bottom: 1px solid orange;  border-radius: 0px; background-color: rgb(58, 89, 92);  min-width: 0px; color:"+this->globalBackgroundColor );
    }
    else{
        patientsWidgetOption->setStyleSheet( "border-bottom: 1px solid orange;  border-radius: 0px; background-color:"+this->globalBackgroundColor+";  min-width: 0px; color: rgb(58, 89, 92) " );
    }
}

//--------------------------------------------------------------------------------------------------------------------------------
//!
//! \brief pissMainWindow::onSystemWidgetOptionHovered
//!
void pissMainWindow::onSystemWidgetOptionHovered(){
    if(!mainOptionStates.systemWidgetOptionState){
        systemWidgetOption->setStyleSheet( "border-bottom: 1px solid orange;  border-radius: 0px; background-color: gainsboro;  min-width: 0px; color:"+this->globalBackgroundColor );
    }
}

//--------------------------------------------------------------------------------------------------------------------------------
//!
//! \brief pissMainWindow::onSystemWidgetOptionClicked
//!
void pissMainWindow::onSystemWidgetOptionClicked(){
    systemWidgetOption->setStyleSheet( "border-bottom: 1px solid orange;  border-radius: 0px; background-color: transparent;  min-width: 0px; color:"+this->globalBackgroundColor );
}

//--------------------------------------------------------------------------------------------------------------------------------
//!
//! \brief pissMainWindow::onSystemWidgetOptionReleased
//!
void pissMainWindow::onSystemWidgetOptionReleased(){
    patientsWidgetOption->setStyleSheet( "border-bottom: 1px solid orange;  border-radius: 0px; background-color:"+this->globalBackgroundColor+";  min-width: 0px; color: rgb(58, 89, 92)  "  );
    systemWidgetOption->setStyleSheet( "border-bottom: 1px solid orange;  border-radius: 0px; background-color: rgb(58, 89, 92);  min-width: 0px; color: "+this->globalBackgroundColor );
    historyWidgetOption->setStyleSheet( "border-bottom: 1px solid orange;  border-radius: 0px; background-color: "+this->globalBackgroundColor+";   min-width: 0px; color: rgb(58, 89, 92)  "  );

    patientsWidgetOption->setFont(QFont("Segoe UI", 12, QFont::AnyStyle, true));
    systemWidgetOption->setFont(QFont("Segoe UI", 12, QFont::DemiBold, true));
    historyWidgetOption->setFont(QFont("Segoe UI", 12, QFont::AnyStyle, true));

    mainOptionStates.patientsWidgetOptionState = false;
    mainOptionStates.systemWidgetOptionState = true;
    mainOptionStates.historyWidgetOptionState = false;

    patientsWidget->close();
    surgerySystemWidget->show();
    replaysWidget->close();

}

//--------------------------------------------------------------------------------------------------------------------------------
//!
//! \brief pissMainWindow::onSystemWidgetOptionLeaved
//!
void pissMainWindow::onSystemWidgetOptionLeaved(){
    if(mainOptionStates.systemWidgetOptionState){
        systemWidgetOption->setStyleSheet( "border-bottom: 1px solid orange;  border-radius: 0px; background-color: rgb(58, 89, 92);  min-width: 0px; color: "+this->globalBackgroundColor );
    }
    else{
        systemWidgetOption->setStyleSheet( "border-bottom: 1px solid orange;  border-radius: 0px; background-color: "+this->globalBackgroundColor+";   min-width: 0px; color: rgb(58, 89, 92) " );
    }
}

//--------------------------------------------------------------------------------------------------------------------------------
//!
//! \brief pissMainWindow::onHistoryWidgetOptionHovered
//!
void pissMainWindow::onHistoryWidgetOptionHovered(){
    if(!mainOptionStates.historyWidgetOptionState){
        historyWidgetOption->setStyleSheet( "border-bottom: 1px solid orange;  border-radius: 0px; background-color: gainsboro;  min-width: 0px; color:"+this->globalBackgroundColor );
    }
}

//--------------------------------------------------------------------------------------------------------------------------------
//!
//! \brief pissMainWindow::onHistoryWidgetOptionClicked
//!
//!
void pissMainWindow::onHistoryWidgetOptionClicked(){
   historyWidgetOption->setStyleSheet( "border-bottom: 1px solid orange;  border-radius: 0px; background-color: transparent;  min-width: 0px; color: "+this->globalBackgroundColor );
}

//--------------------------------------------------------------------------------------------------------------------------------
//!
//! \brief pissMainWindow::onHistoryWidgetOptionReleased
//!
void pissMainWindow::onHistoryWidgetOptionReleased(){
    patientsWidgetOption->setStyleSheet( "border-bottom: 1px solid orange;  border-radius: 0px; background-color: "+this->globalBackgroundColor+";   min-width: 0px; color: rgb(58, 89, 92)  "  );
    systemWidgetOption->setStyleSheet( "border-bottom: 1px solid orange;  border-radius: 0px; background-color: "+this->globalBackgroundColor+";   min-width: 0px; color: rgb(58, 89, 92)  "  );
    historyWidgetOption->setStyleSheet( "border-bottom: 1px solid orange;  border-radius: 0px; background-color: rgb(58, 89, 92);  min-width: 0px; color:"+this->globalBackgroundColor);

    patientsWidgetOption->setFont(QFont("Segoe UI", 12, QFont::AnyStyle, true));
    systemWidgetOption->setFont(QFont("Segoe UI", 12, QFont::AnyStyle, true));
    historyWidgetOption->setFont(QFont("Segoe UI", 12, QFont::DemiBold, true));

    mainOptionStates.patientsWidgetOptionState = false;
    mainOptionStates.systemWidgetOptionState = false;
    mainOptionStates.historyWidgetOptionState = true;
    widgetOptionContainer->setStyleSheet("background-color: rgb(58, 89, 92)");

    patientsWidget->close();
    surgerySystemWidget->close();
    replaysWidget->show();
}

//--------------------------------------------------------------------------------------------------------------------------------
//!
//! \brief pissMainWindow::onHistoryWidgetOptionLeaved
//!
void pissMainWindow::onHistoryWidgetOptionLeaved(){
    if(mainOptionStates.historyWidgetOptionState){
        historyWidgetOption->setStyleSheet( "border-bottom: 1px solid orange;  border-radius: 0px; background-color: rgb(58, 89, 92);  min-width: 0px; color:"+this->globalBackgroundColor);
    }
    else{
        historyWidgetOption->setStyleSheet( "border-bottom: 1px solid orange;  border-radius: 0px; background-color: "+this->globalBackgroundColor+";   min-width: 0px; color: rgb(58, 89, 92) " );
    }
}

//--------------------------------------------------------------------------------------------------------------------------------
//!
//! \brief IgssMainWindow::mouseMoveEvent
//! \param event
//!
void pissMainWindow::mouseMoveEvent(QMouseEvent *event){
//    if(buttonGaucheDuSourisClique == true){
//        mouseMovingPosition = event->globalPos();
//        this->move(this->pos() + mouseMovingPosition - mousePosition);
//        mousePosition = mouseMovingPosition;
//    }
    event->ignore();
}

//--------------------------------------------------------------------------------------------------------------------------------
//!
//! \brief IgssMainWindow::mousePressEvent
//! \param event
//!
void pissMainWindow::mousePressEvent(QMouseEvent *event){
//    if(event->button() == Qt::LeftButton){
//       if (!((event->y() < 5) || (event->x() <5))){
//           mousePosition = event->globalPos();
//           buttonGaucheDuSourisClique = true;
//       }
//    }
    event->ignore();
}

//--------------------------------------------------------------------------------------------------------------------------------
//!
//! \brief IgssMainWindow::mouseReleaseEvent
//! \param event
//!
void pissMainWindow::mouseReleaseEvent(QMouseEvent *event){
//    if(event->button() == Qt::LeftButton){
//        buttonGaucheDuSourisClique = false;
//    }
    event->ignore();
}

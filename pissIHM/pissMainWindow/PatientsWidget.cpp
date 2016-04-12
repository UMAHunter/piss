#include "PatientsWidget.h"

PatientsWidget::PatientsWidget(int screen_count,
                               SystemDispatcher* dispatcher,
                               AlgorithmTestPlatform *algorithmTestPlatform,
                               PatientInformationWidget* patientInformationWidget,
                               QTime* surgeryTimer,
                               QFont *caracterStyle,
                               int appWidth,
                               int appHeight,
                               QString workspaceColor) : QWidget(){
    this->screen_count = screen_count;

    this->dispatcher = dispatcher;
    this->algorithmTestPlatform = algorithmTestPlatform;

    this->patientInformationWidget = patientInformationWidget;

    this->surgeryTimer = surgeryTimer;
    this->caracterStyle = caracterStyle;
    this->appWidth = appWidth;
    this->appHeight = appHeight;
    this->workspaceColor = workspaceColor;

    this->initVariable();
    this->constructIHM();
    this->setConnections();
    this->setFocusPolicy(Qt::StrongFocus);
    this->setFixedSize(this->appWidth, this->appHeight);

    setWorkSpaceColor(this->workspaceColor);
}

//!----------------------------------------------------------------------------------------------------
//!
//! \brief PatientsWidget::drawBackground
//! \param widget
//! \param path
//!
void PatientsWidget::drawBackground(QWidget *widget, QString path, int w, int h){
    QPixmap *pixmap = new QPixmap(path);
    QPalette palette;

    palette.setBrush(QPalette::Background, QBrush(pixmap->scaled(QSize(w, h), Qt::IgnoreAspectRatio, Qt::SmoothTransformation)));
    widget->setPalette(palette);
    widget->setMask(pixmap->mask());
}

//!----------------------------------------------------------------------------------------------------
//!
//! \brief PatientsWidget::setSurgeryPlanWindow
//! \param surgeryPlanWindow
//!
void PatientsWidget::setSurgeryPlanWindow(SurgeryPlanWindow* surgeryPlanWindow){
    this->surgeryPlanWindow = surgeryPlanWindow;
}

//!----------------------------------------------------------------------------------------------------
//!
//! \brief PatientsWidget::setGuidewareTrackingWindow
//! \param guidewareTrackingWindow
//!
void PatientsWidget::setGuidewareTrackingWindow(GuidewareTrackingWindow* guidewareTrackingWindow){
    this->guidewareTrackingWindow = guidewareTrackingWindow;
}

//!----------------------------------------------------------------------------------------------------
//!
//! \brief PatientsWidget::setControlConsoleWindow
//! \param controlConsoleWindow
//!
void PatientsWidget::setControlConsoleWindow(ControlConsoleWindow * controlConsoleWindow){
    this->controlConsoleWindow = controlConsoleWindow;
}

//!----------------------------------------------------------------------------------------------------
//!
//! \brief PatientsWidget::displayLastFiveOrLess
//!
void PatientsWidget::displayLastFiveOrLess(){

    int offset = numberOfPatient - 5;

    for(int cpt = 5; cpt > 0; cpt--){
        waitingPatientsQueue.at(numberOfPatient - cpt - offset)->setPixmap(waitingPatientsPhotoStringQueue.at(numberOfPatient - cpt - offset));
        waitingPatientsQueue.at(numberOfPatient - cpt - offset)->setAutoFillBackground(true);
        waitingPatientsQueue.at(numberOfPatient - cpt - offset)->setScaledContents(true);
        waitingPatientsQueue.at(numberOfPatient - cpt - offset)->update();

        waitingPatientsNameQueue.at(numberOfPatient - cpt - offset)->setText(waitingPatientsStringNameQueue.at(numberOfPatient - cpt - offset));
        waitingPatientsNameQueue.at(numberOfPatient - cpt - offset)->setAutoFillBackground(true);
        waitingPatientsNameQueue.at(numberOfPatient - cpt - offset)->setScaledContents(true);
        waitingPatientsNameQueue.at(numberOfPatient - cpt - offset)->update();
    }

}

//!----------------------------------------------------------------------------------------------------
//!
//! \brief PatientsWidget::doLeftSelect
//!
void PatientsWidget::doLeftSelect(){
    if(this->surgeryLaunched){
        return;
    }

    if(this->surgeryTerminated){

        QString temp;
        temp = this->waitingPatientsPhotoStringQueue.at(0);
        this->waitingPatientsPhotoStringQueue.pop_front();
        this->waitingPatientsPhotoStringQueue.append(temp);

        QString temp1;
        temp1 = this->waitingPatientsStringNameQueue.at(0);
        this->waitingPatientsStringNameQueue.pop_front();
        this->waitingPatientsStringNameQueue.append(temp1);

        QString temp2;
        temp2 = this->waitingPatientsIDQueue.at(0);
        this->waitingPatientsIDQueue.pop_front();
        this->waitingPatientsIDQueue.append(temp2);

        QString temp3;
        temp3 = this->waitingPatientsMraPathQueue.at(0);
        this->waitingPatientsMraPathQueue.pop_front();
        this->waitingPatientsMraPathQueue.append(temp3);

        this->displayLastFiveOrLess();
        this->displayCurrentPatinetInfo();
        this->displayBrainSegImage();
    }

}

//!----------------------------------------------------------------------------------------------------
//!
//! \brief PatientsWidget::doRightSelect
//!
void PatientsWidget::doRightSelect(){
    if(this->surgeryLaunched){
        return;
    }

    if(this->surgeryTerminated){
        QString temp;
        temp = this->waitingPatientsPhotoStringQueue.at(this->numberOfPatient-1);

        this->waitingPatientsPhotoStringQueue.pop_back();
        this->waitingPatientsPhotoStringQueue.insert(0,temp);

        QString temp1;
        temp1 = this->waitingPatientsStringNameQueue.at(this->numberOfPatient-1);
        this->waitingPatientsStringNameQueue.pop_back();
        this->waitingPatientsStringNameQueue.insert(0,temp1);

        QString temp2;
        temp2 = this->waitingPatientsIDQueue.at(this->numberOfPatient-1);
        this->waitingPatientsIDQueue.pop_back();
        this->waitingPatientsIDQueue.insert(0,temp2);

        QString temp3;
        temp3 = this->waitingPatientsMraPathQueue.at(this->numberOfPatient-1);
        this->waitingPatientsMraPathQueue.pop_back();
        this->waitingPatientsMraPathQueue.insert(0,temp3);

        this->displayLastFiveOrLess();
        this->displayCurrentPatinetInfo();
        this->displayBrainSegImage();
    }
}

void PatientsWidget::setPatientHandling(Patient *patientHandling){
    this->patientHandling = patientHandling;
}

//!----------------------------------------------------------------------------------------------------
//!
//! \brief PatientsWidget::findPatientExisted
//!
void PatientsWidget::findPatientExisted(){
    numberOfPatient = this->dispatcher->findPatientExisted();

    //!algorithmTestPlatform->setSystemStatus(QString::number(numberOfPatient));

    for(int cpt = numberOfPatient; cpt > 0; cpt--){
        waitingPatientsPhotoStringQueue.append(this->dispatcher->getPatientById(numberOfPatient - cpt)->getPhotoPath());
        waitingPatientsStringNameQueue.append(this->dispatcher->getPatientById(numberOfPatient - cpt)->getName());
        waitingPatientsIDQueue.append(QString::number(numberOfPatient - cpt));
        waitingPatientsMraPathQueue.append(this->dispatcher->getPatientById(numberOfPatient - cpt)->getMraTridimensionelPath());
    }

    currentPatinetInfoQueue.append(this->dispatcher->getPatientById(numberOfPatient - 1)->getBirthdayOfPatient());
    //currentPatinetInfoQueue.append(this->dispatcher->getPatientById(numberOfPatient - 1)->getSexOfPatient());
    //currentPatinetInfoQueue.append(this->dispatcher->getPatientById(numberOfPatient - 1)->getIdNumber());

    this->displayLastFiveOrLess();
    this->displayCurrentPatinetInfo();
    displayBrainSegImage();
}

//!----------------------------------------------------------------------------------------------------
//!
//! \brief PatientsWidget::initVariable
//!
void PatientsWidget::initVariable(){
    this->surgeryLaunched = false;
    this->surgeryTerminated = true;
    this->numberOfPatient  = 0;
    this->dicomCDRomReader = new DicomCDRomReader();
    this->photoLabelStyleSheet = "border: 0px solid aliceBlue;border-radius: 0px;padding: 2 2px;background-color: transparent; color: AliceBlue";
    this->labelStyleSheet = "border: 0px solid aliceBlue;border-radius: 0px;background-color: transparent; color: AliceBlue";
    this->textEditStyleSheet = "border: 0px solid aliceBlue; color: AliceBlue; background-color: transparent";
    this->caracterFontStyle = new QFont("Times",10,QFont::AnyStyle, false);

    this->superviseWindow = new SuperviseWindow(appWidth, appHeight);

    this->volumeMapper = vtkFixedPointVolumeRayCastMapper::New();
    this->compositeFunction = vtkVolumeRayCastCompositeFunction::New();
    this->volume = vtkVolume::New();
    this->renderWindow = vtkSmartPointer<vtkRenderWindow>::New() ;
    this->renderer = vtkSmartPointer<vtkRenderer>::New();
    this->volumeProperty = vtkVolumeProperty::New();
    this->volumeProperty->ShadeOff();
    this->volumeProperty->SetInterpolationType(VTK_LINEAR_INTERPOLATION);
    vtkSmartPointer<vtkPiecewiseFunction> compositeOpacity = vtkSmartPointer<vtkPiecewiseFunction>::New();
    compositeOpacity->AddPoint(0.0,   0.0);
    compositeOpacity->AddPoint(800.0, 0.0);
    compositeOpacity->AddPoint(1200.0,1.0);
    compositeOpacity->AddPoint(2000.0,1.0);
    this->volumeProperty->SetScalarOpacity(compositeOpacity); // composite first.

    vtkSmartPointer<vtkColorTransferFunction> color = vtkSmartPointer<vtkColorTransferFunction>::New();
    color->AddRGBPoint(0.0,    0.0,0.0,1.0);
    color->AddRGBPoint(800.0,  1.0,0.0,0.0);
    color->AddRGBPoint(1200.0, 1.0,1.0,1.0);
    color->AddRGBPoint(2000.0, 1.0,1.0,1.0);
    this->volumeProperty->SetColor(color);
}

//!----------------------------------------------------------------------------------------------------
//!
//! \brief PatientsWidget::setConnections
//!
void PatientsWidget::setConnections(){
    this->connect(this->cdRomParseButton, SIGNAL(clicked()), this, SLOT(doParseCdRom()));
    this->connect(this->surgeryLaunchButton, SIGNAL(clicked()), this, SLOT(launchSurgery()));
    this->connect(this->addPatientButton, SIGNAL(clicked()), this, SLOT(addPatient()));
    this->connect(this->leftSelectButton, SIGNAL(clicked()), this, SLOT(doLeftSelect()));
    this->connect(this->rightSelectButton, SIGNAL(clicked()), this, SLOT(doRightSelect()));
}


//!----------------------------------------------------------------------------------------------------
//!
//! \brief PatientsWidget::displayCurrentPatinetInfo
//!
void PatientsWidget::displayCurrentPatinetInfo(){
    //this->nameLineEdit->setText(waitingPatientsStringNameQueue.at(4));
    //this->birthdayLineEdit->setText(currentPatinetInfoQueue.at(0));
    //this->sexualLineEdit->setText(currentPatinetInfoQueue.at(1));
    //this->idNumberEdit->setText(currentPatinetInfoQueue.at(1));
}

//!----------------------------------------------------------------------------------------------------
//!
//! \brief PatientsWidget::launchSurgery
//!
void PatientsWidget::launchSurgery(){

    if(screen_count != 3){
        QMessageBox::StandardButton reply;
        reply = QMessageBox::question(this, "Not enough screen available", "branche le?",
                                    QMessageBox::Yes|QMessageBox::No);
        return;
    }

    //! -----------------------------------------
    //!TODO: loading tasks execute......

    //! ......
    //this->surgeryLaunchButton->setFixedSize(0,0);
    //this->surgeryTerminateButton->setFixedSize(this->appWidth*0.15,this->appHeight/0.79*0.846*0.15*0.3);
    this->surgeryLaunchButton->setEnabled(false);

    this->surgeryLaunchButton->setStyleSheet("background-color:transparent;border:1px solid gray;color:gray");
    this->leftSelectButton->setEnabled(false);
    this->rightSelectButton->setEnabled(false);
    this->surgeryLoadingBar->setValue(10);

    //! -----------------------------------------
    //! fetch the pointer of the patient handling
    Patient *patientHandling = this->dispatcher->getPatientById(waitingPatientsIDQueue[4].toInt(0,10));
    this->surgeryLoadingBar->setValue(20);

    //! duchengcheng, duyue, qiujiaqing
    this->surgeryPlanWindow->setPatientHandling(patientHandling);
    this->surgeryPlanWindow->update();
    this->surgeryLoadingBar->setValue(30);

    //! wangcheng, fandeyuan
    this->guidewareTrackingWindow->setPatientHandling(patientHandling);
    this->guidewareTrackingWindow->update();
    this->surgeryLoadingBar->setValue(50);

    //! apres
    //this->superviseWindow->show();

    emit surgeryLaunchButtonCicked();

    //! -----------------------------------------
    //! loading task terminated......
    //!-----------------------------------------

    this->surgeryPlanWindow->displayWindow();
    this->guidewareTrackingWindow->displayWindow();
    this->controlConsoleWindow->showFullScreen();

    this->surgeryLaunched = true;

    this->surgeryTimer->start();
    this->surgeryPlanWindow->setStartTime(this->surgeryTimer->elapsed());

    //! TODO: to be modified!!!!
    this->guidewareTrackingWindow->realTimeVideoPlay();
    this->guidewareTrackingWindow->lastFramePlay();
    // this->guidewareTrackingWindow->VTKDisplay();
    // this->guidewareTrackingWindow->VTKFlowDisplay();

}

//!----------------------------------------------------------------------------------------------------
//!
//! \brief PatientsWidget::terminateSurgery
//!
void PatientsWidget::terminateSurgery(){

    //this->surgeryLaunchButton->setFixedSize(this->appWidth*0.15,this->appHeight/0.79*0.846*0.15*0.3);
    this->surgeryLaunchButton->setText("launch");
    this->surgeryLaunchButton->setEnabled(true);
    this->leftSelectButton->setEnabled(true);
    this->rightSelectButton->setEnabled(true);
    this->surgeryLaunched = false;
    this->surgeryTerminated = true;
    this->surgeryPlanWindow->close();
    this->guidewareTrackingWindow->close();

}

//!----------------------------------------------------------------------------------------------------
//!
//! \brief PatientsWidget::doParseCdRom
//!
void PatientsWidget::doParseCdRom(){
    this->algorithmTestPlatform->setSystemStatus("doParseCdRom");

    //TODO
    //dicomCDRomReader->doParseCDRom(.......);
}

//!----------------------------------------------------------------------------------------------------
//!
//! \brief PatientsWidget::addPatient
//!
void PatientsWidget::addPatient(){
    this->patientInformationWidget->display(QCursor::pos());
}

//!----------------------------------------------------------------------------------------------------
//!
//! \brief PatientsWidget::testX
//! \return
//!
int PatientsWidget::testX(){
    return firstPatientPhotoWidget->width();
}

//!----------------------------------------------------------------------------------------------------
//!
//! \brief PatientsWidget::testY
//! \return
//!
int PatientsWidget::testY(){
    return firstPatientPhotoWidget->height();
}

//!----------------------------------------------------------------------------------------------------
//!
//! \brief PatientsWidget::displayBrainSegImage
//!
void PatientsWidget::displayBrainSegImage(){

    loadMRAImageFile(waitingPatientsMraPathQueue.at(4));

    this->algorithmTestPlatform->setSystemStatus(waitingPatientsMraPathQueue.at(4));
}

//!----------------------------------------------------------------------------------------------------
//!
//! \brief Patient::loadMRAImageFile
//! \param fileName
//! \return
//!
bool PatientsWidget::loadMRAImageFile(const QString &fileName){
    //! file type check
    eFileType ret =  ImageFileInterface::getFileType(fileName);

    if(ret == UNKOWN_FILE_TYPE){
        return false;
    }

    //! get the instance of related reader according to the file type
    ImageFileInterface *fileInterface = ImageFileInterface::getInstanceFileByType(ret);

    //! read the content of the image
    if(fileInterface->readFrom(fileName) != IMAGE_NO_ERRROR){
        return false;
    }

    //!Pass the reference of the image read to the pointer declared upon
    display(fileInterface->getImage());


    return true;
}

//! --------------------------------------------------------------------------------------------------------
//!
//! \brief PatientsWidget::setWorkSpaceColor
//! \param workspaceColor
//!
void PatientsWidget::setWorkSpaceColor(QString workspaceColor){
    QColor *qworkspaceColor = new QColor(workspaceColor);

    workspaceRed = qworkspaceColor->red();
    workspaceGreen = qworkspaceColor->green();
    workspaceBlue = qworkspaceColor->blue();

    this->renderer->SetBackground((1.0*workspaceRed)/255, (1.0*workspaceGreen)/255, (1.0*workspaceBlue)/255);
}

//! --------------------------------------------------------------------------------------------------------
//!
//! \brief PatientsWidget::display
//! \param imgToBeDisplayed
//!
void PatientsWidget::display(vtkImageData *imgToBeDisplayed){

    //!---------------------------------------------------------------
    //! volume data visualization
    //!---------------------------------------------------------------
    this->volumeMapper->SetInputData(imgToBeDisplayed);
    this->volumeMapper->SetBlendModeToMaximumIntensity();
    this->volume->SetMapper(volumeMapper);
    this->volume->SetProperty(volumeProperty);

    this->renderer->AddVolume(volume);

    this->renderWindow->AddRenderer(renderer);

    this->patientImageLoaded->SetRenderWindow(renderWindow);
    this->renderer->SetBackground((1.0*workspaceRed)/255, (1.0*workspaceGreen)/255, (1.0*workspaceBlue)/255);

    this->renderer->ResetCamera();
    this->renderWindow->Render();
}

//! --------------------------------------------------------------------------------------------------------
//!
//! \brief PatientsWidget::update
//!
void PatientsWidget::update(){

    this->patientHandling->doImageFileLecture();

    //! wait lecture finished
    do{
        this->algorithmTestPlatform->setSystemStatus("unfinished");
    }while(!this->patientHandling->readFinished());

    //this->algorithmTestPlatform->setSystemStatus("finished");
    this->displayBrainSegImage();
}

//!----------------------------------------------------------------------------------------------------
//!
//! \brief PatientsWidget::constructIHM
//!
void PatientsWidget::constructIHM(){

    //! ---------------------------------------------------------------------------------------------------------------------
    this->patientsWidgetToolBar = new QWidget();

    this->patientsWidgetToolBar->setStyleSheet("background-color:"+this->workspaceColor);
    this->patientsWidgetToolBar->setFixedHeight(this->appHeight*0.03);

    this->simpleModeButton =  new QPushButton();
    this->simpleModeButton->setIcon(QIcon(":/images/fileList.png"));
    this->simpleModeButton->setIconSize(QSize(this->appWidth*0.02,this->appHeight*0.03));
    this->simpleModeButton->setFixedSize(this->appWidth*0.020, this->appHeight*0.03);
    this->simpleModeButton->setFlat(true);

    this->patientsWidgetConfigurationButton =  new QPushButton();
    this->patientsWidgetConfigurationButton->setIcon(QIcon(":/images/import_patient.png"));
    this->patientsWidgetConfigurationButton->setIconSize(QSize(this->appWidth*0.02,this->appHeight*0.03));
    this->patientsWidgetConfigurationButton->setFixedSize(this->appWidth*0.020, this->appHeight*0.03);
    this->patientsWidgetConfigurationButton->setFlat(true);

    this->addPatientButton =  new QPushButton();
    this->addPatientButton->setIcon(QIcon(":/images/patientWidgetConfiguration.png"));
    this->addPatientButton->setIconSize(QSize(this->appWidth*0.02,this->appHeight*0.03));
    this->addPatientButton->setFixedSize(this->appWidth*0.020, this->appHeight*0.03);
    this->addPatientButton->setFlat(true);

    this->cdRomParseButton =  new QPushButton();
    this->cdRomParseButton->setIcon(QIcon(":/images/Disk.png"));
    this->cdRomParseButton->setIconSize(QSize(this->appWidth*0.02,this->appHeight*0.03));
    this->cdRomParseButton->setFixedSize(this->appWidth*0.02, this->appHeight*0.03);
    this->cdRomParseButton->setFlat(true);

    this->controlBarSpacer = new QSpacerItem(20, 20, QSizePolicy::Expanding, QSizePolicy::Expanding);

    this->patientsWidgetToolBarLayout = new QHBoxLayout(this->patientsWidgetToolBar);
    this->patientsWidgetToolBarLayout->addWidget(this->simpleModeButton);
    this->patientsWidgetToolBarLayout->addWidget(this->patientsWidgetConfigurationButton);
    this->patientsWidgetToolBarLayout->addWidget(this->addPatientButton);
    this->patientsWidgetToolBarLayout->addWidget(this->cdRomParseButton);
    this->patientsWidgetToolBarLayout->addSpacerItem(this->controlBarSpacer);
    this->patientsWidgetToolBarLayout->setSpacing(0);
    this->patientsWidgetToolBarLayout->setMargin(0);

    this->upBlackArea = new QWidget();
    this->upBlackArea->setFixedHeight(this->appHeight*0.03);
    this->upBlackArea->setStyleSheet("background-color:transparent; border:0px solid beige");


    this->downBlackArea = new QWidget();
    this->downBlackArea->setFixedHeight(this->appHeight*0.03);
    this->downBlackArea->setStyleSheet("background-color:transparent;border:0px solid beige");

    this->leftBlackArea = new QWidget();
    this->leftBlackArea->setFixedWidth(this->appWidth*0.17);
    this->leftBlackArea->setStyleSheet("background-color:transparent;border:0px solid beige");

    this->rightBlackArea = new QWidget();
    this->rightBlackArea->setFixedWidth(this->appWidth*0.02);
    this->rightBlackArea->setStyleSheet("background-color:transparent;border:0px solid beige");

    this->firstPatientPhotoWidget = new PatientItem(appWidth,appHeight);
    this->firstPatientPhotoWidget->setFixedSize(this->appWidth*0.07, this->appHeight*0.22);

    this->secondPatientPhotoWidget = new PatientItem(appWidth,appHeight);
    this->secondPatientPhotoWidget->setFixedSize(this->appWidth*0.07, this->appHeight*0.22);

    this->thirdPatientPhotoWidget = new PatientItem(appWidth,appHeight);
    this->thirdPatientPhotoWidget->setFixedSize(this->appWidth*0.07, this->appHeight*0.22);

    this->fourthPatientPhotoWidget = new PatientItem(appWidth,appHeight);
    this->fourthPatientPhotoWidget->setFixedSize(this->appWidth*0.07, this->appHeight*0.22);

    this->waittingPatientPhotoes = new QWidget();
    this->waittingPatientPhotoes->setStyleSheet("background-color:transparent;border:0px solid beige");
    this->waittingPatientPhotoesLayout = new QHBoxLayout(waittingPatientPhotoes);
    this->waittingPatientPhotoesLayout->addWidget(leftBlackArea);
    this->waittingPatientPhotoesLayout->addWidget(firstPatientPhotoWidget);
    this->waittingPatientPhotoesLayout->addWidget(secondPatientPhotoWidget);
    this->waittingPatientPhotoesLayout->addWidget(thirdPatientPhotoWidget);
    this->waittingPatientPhotoesLayout->addWidget(fourthPatientPhotoWidget);
    this->waittingPatientPhotoesLayout->addWidget(rightBlackArea);
    this->waittingPatientPhotoesLayout->setSpacing(10);
    this->waittingPatientPhotoesLayout->setMargin(0);

    this->waittingPatientsAndBlackAreaWindow = new QWidget();
    this->waittingPatientsAndBlackAreaWindow->setStyleSheet("background-color:transparent; border:0px solid beige");
    this->waittingPatientsAndBlackAreaWindowLayout = new QVBoxLayout(waittingPatientsAndBlackAreaWindow);
    this->waittingPatientsAndBlackAreaWindowLayout->addWidget(upBlackArea);
    this->waittingPatientsAndBlackAreaWindowLayout->addWidget(waittingPatientPhotoes);
    this->waittingPatientsAndBlackAreaWindowLayout->addWidget(downBlackArea);
    this->waittingPatientsAndBlackAreaWindowLayout->setSpacing(0);
    this->waittingPatientsAndBlackAreaWindowLayout->setMargin(0);

    //!--------------------------------------------------------------------------------------
    //!current patient widget
    //!--------------------------------------------------------------------------------------
    this->currentPatientPhoto = new QLabel();
    this->currentPatientPhoto->setStyleSheet(this->photoLabelStyleSheet);
    this->currentPatientPhoto->setFixedHeight(this->appHeight*0.2);

    this->currentPatientInfo = new QLabel();
    this->currentPatientInfo->setFont(*this->caracterStyle);
    this->currentPatientInfo->setStyleSheet(this->labelStyleSheet);
    this->currentPatientInfo->setFixedHeight(this->appHeight*0.03);
    this->currentPatientInfo->setAlignment(Qt::AlignCenter);

    this->currentPatientBreifInformationWidget = new QWidget();
    this->currentPatientBreifInformationWidget->setStyleSheet("background-color:transparent; border:0px solid aliceblue; ");
    this->currentPatientBreifInformationWidget->setFixedWidth(this->appWidth*0.1);
    this->currentPatientBreifInformationWidgetLayout = new QVBoxLayout(this->currentPatientBreifInformationWidget);
    this->currentPatientBreifInformationWidgetLayout->addWidget(this->currentPatientPhoto);
    this->currentPatientBreifInformationWidgetLayout->addWidget(this->currentPatientInfo);
    this->currentPatientBreifInformationWidgetLayout->setSpacing(0);
    this->currentPatientBreifInformationWidgetLayout->setMargin(0);

    this->waitingPatientsQueue.append(this->firstPatientPhotoWidget->getPatientPhoto());
    this->waitingPatientsQueue.append(this->secondPatientPhotoWidget->getPatientPhoto());
    this->waitingPatientsQueue.append(this->thirdPatientPhotoWidget->getPatientPhoto());
    this->waitingPatientsQueue.append(this->fourthPatientPhotoWidget->getPatientPhoto());
    this->waitingPatientsQueue.append(this->currentPatientPhoto);

    this->waitingPatientsNameQueue.append(this->firstPatientPhotoWidget->getPatientName());
    this->waitingPatientsNameQueue.append(this->secondPatientPhotoWidget->getPatientName());
    this->waitingPatientsNameQueue.append(this->thirdPatientPhotoWidget->getPatientName());
    this->waitingPatientsNameQueue.append(this->fourthPatientPhotoWidget->getPatientName());
    this->waitingPatientsNameQueue.append(this->currentPatientInfo);

    this->surgeryLaunchButton = new QPushButton();
    this->surgeryLaunchButton->setText(QString::fromLocal8Bit("launch"));
    this->surgeryLaunchButton->setFont(QFont("Times",13,QFont::AnyStyle, false));
    this->surgeryLaunchButton->setStyleSheet("background-color:skyblue;border:0px solid aliceblue;color:teal");
    this->surgeryLaunchButton->setFixedSize(this->appWidth*0.1, this->appHeight*0.05);

    this->patientHandlingWidget = new QWidget();
    this->patientHandlingWidget->setStyleSheet("background-color:transparent; border:0px solid aliceblue; ");
    this->patientHandlingWidget->setFixedSize(this->appWidth*0.1, this->appHeight*0.28);
    this->patientHandlingWidgetLayout = new QVBoxLayout(patientHandlingWidget);
    this->patientHandlingWidgetLayout->addWidget(currentPatientBreifInformationWidget);
    this->patientHandlingWidgetLayout->addWidget(surgeryLaunchButton);
    this->patientHandlingWidgetLayout->setSpacing(0);
    this->patientHandlingWidgetLayout->setMargin(0);

    //!--------------------------------------------------------------------------------------
    //!the right select button
    //!--------------------------------------------------------------------------------------
    this->leftSelectButton = new QPushButton();
    this->leftSelectButton->setFixedSize(this->appWidth*0.015,this->appHeight*0.28);
    this->leftSelectButton->setIcon(QIcon(":/images/splitter_left.png"));
    this->leftSelectButton->setStyleSheet("background-color:transparent; border:0px solid aliceblue; ");
    this->leftSelectButton->setFlat(true);

    this->rightSelectButton = new QPushButton();
    this->rightSelectButton->setFixedSize(this->appWidth*0.015,this->appHeight*0.28);
    this->rightSelectButton->setIcon(QIcon(":/images/splitter_right.png"));
    this->rightSelectButton->setStyleSheet("background-color:transparent; border:0px solid aliceblue;");
    this->rightSelectButton->setFlat(true);

    //!--------------------------------------------------------------------------------------
    //!patient photo widget: there are 3 photoes of waitting patients and 1 current patient
    //!--------------------------------------------------------------------------------------
    this->patientsPhotoWidget = new QWidget();
    this->patientsPhotoWidget->setFixedSize(this->appWidth*0.6, this->appHeight*0.28);
    //this->patientsPhotoWidget->setStyleSheet("border-image: url(:images/background.png); border:1px solid beige;");
    this->patientsPhotoWidgetLayout = new QHBoxLayout(this->patientsPhotoWidget);
    this->patientsPhotoWidgetLayout->addWidget(waittingPatientsAndBlackAreaWindow);
    this->patientsPhotoWidgetLayout->addWidget(leftSelectButton);
    this->patientsPhotoWidgetLayout->addWidget(patientHandlingWidget);
    this->patientsPhotoWidgetLayout->addWidget(rightSelectButton);
    this->patientsPhotoWidgetLayout->setSpacing(0);
    this->patientsPhotoWidgetLayout->setMargin(0);
    //drawBackground(this->patientsPhotoWidget, ":/images/background.png",this->appWidth*0.6, this->appHeight*0.28);

    this->patientImageLoaded = new QVTKWidget();
    this->patientImageLoaded->setFixedSize(this->appWidth*0.6, this->appHeight*0.64);

    this->patientsPhotoAndMedicaleImageContainerWidget = new QFrame();
    this->patientsPhotoAndMedicaleImageContainerWidget->setStyleSheet("background-color:"+this->workspaceColor);
    this->patientsPhotoAndMedicaleImageContainerWidget->setFixedWidth(this->appWidth*0.6);
    this->patientsPhotoAndMedicaleImageContainerWidgetLayout = new QVBoxLayout(patientsPhotoAndMedicaleImageContainerWidget);
    this->patientsPhotoAndMedicaleImageContainerWidgetLayout->addWidget(patientsPhotoWidget);
    this->patientsPhotoAndMedicaleImageContainerWidgetLayout->addWidget(patientImageLoaded);
    this->patientsPhotoAndMedicaleImageContainerWidgetLayout->setSpacing(0);
    this->patientsPhotoAndMedicaleImageContainerWidgetLayout->setMargin(0);

    //!--------------------------------------------------------------------------------------
    //!the information of the current patient
    //!--------------------------------------------------------------------------------------
    this->nameLabel = new QLabel("name: ");
    this->nameLabel->setFixedSize(appWidth*0.055,appHeight*0.03);
    this->nameLabel->setFont(*this->caracterFontStyle);
    this->nameLabel->setStyleSheet(this->labelStyleSheet);

    this->birthdayLabel = new QLabel("birth: ");
    this->birthdayLabel->setFixedSize(appWidth*0.055,appHeight*0.03);
    this->birthdayLabel->setFont(*this->caracterFontStyle);
    this->birthdayLabel->setStyleSheet(this->labelStyleSheet);

    this->sexualLabel = new QLabel("sex: ");
    this->sexualLabel->setFixedSize(appWidth*0.055,appHeight*0.03);
    this->sexualLabel->setFont(*this->caracterFontStyle);
    this->sexualLabel->setStyleSheet(this->labelStyleSheet);

    this->ageLabel = new QLabel("age: ");
    this->ageLabel->setFixedSize(appWidth*0.055,appHeight*0.03);
    this->ageLabel->setFont(*this->caracterFontStyle);
    this->ageLabel->setStyleSheet(this->labelStyleSheet);

    this->idNumberLabel = new QLabel("number: ");
    this->idNumberLabel->setFixedSize(appWidth*0.055,appHeight*0.03);
    this->idNumberLabel->setFont(*this->caracterFontStyle);
    this->idNumberLabel->setStyleSheet(this->labelStyleSheet);

    this->marryLabel = new QLabel("marriage: ");
    this->marryLabel->setFixedSize(appWidth*0.055,appHeight*0.03);
    this->marryLabel->setFont(*this->caracterFontStyle);
    this->marryLabel->setStyleSheet(this->labelStyleSheet);

    this->nationLabel = new QLabel("nationality: ");
    this->nationLabel->setFixedSize(appWidth*0.055,appHeight*0.03);
    this->nationLabel->setFont(*this->caracterFontStyle);
    this->nationLabel->setStyleSheet(this->labelStyleSheet);

    this->professionalLabel = new QLabel("professionnel: ");
    this->professionalLabel->setFixedSize(appWidth*0.055,appHeight*0.03);
    this->professionalLabel->setFont(*this->caracterFontStyle);
    this->professionalLabel->setStyleSheet(this->labelStyleSheet);

    this->leadDoctorLabel = new QLabel("doctor: ");
    this->leadDoctorLabel->setFixedSize(appWidth*0.055,appHeight*0.03);
    this->leadDoctorLabel->setFont(*this->caracterFontStyle);
    this->leadDoctorLabel->setStyleSheet(this->labelStyleSheet);

    this->therapyTimeLabel = new QLabel("therapy date: ");
    this->therapyTimeLabel->setFixedSize(appWidth*0.055,appHeight*0.03);
    this->therapyTimeLabel->setFont(*this->caracterFontStyle);
    this->therapyTimeLabel->setStyleSheet(this->labelStyleSheet);

    this->drugAllergyLabel = new QLabel("drug allergy: ");
    this->drugAllergyLabel->setFixedSize(appWidth*0.055,appHeight*0.03);
    this->drugAllergyLabel->setFont(*this->caracterFontStyle);
    this->drugAllergyLabel->setStyleSheet(this->labelStyleSheet);

    this->remarksLabel = new QLabel("ps: ");
    this->remarksLabel->setFixedSize(appWidth*0.055,appHeight*0.03);
    this->remarksLabel->setFont(*this->caracterFontStyle);
    this->remarksLabel->setStyleSheet(this->labelStyleSheet);

    this->nameLineEdit = new QLineEdit();
    this->nameLineEdit->setFixedHeight(appHeight*0.03);
    this->nameLineEdit->setFont(*this->caracterFontStyle);
    this->nameLineEdit->setStyleSheet(this->labelStyleSheet);

    this->birthdayLineEdit = new QLineEdit();
    this->birthdayLineEdit->setFixedHeight(appHeight*0.03);
    this->birthdayLineEdit->setFont(*this->caracterFontStyle);
    this->birthdayLineEdit->setStyleSheet(this->labelStyleSheet);

    this->sexualLineEdit = new QLineEdit();
    this->sexualLineEdit->setFixedHeight(appHeight*0.03);
    this->sexualLineEdit->setFont(*this->caracterFontStyle);
    this->sexualLineEdit->setStyleSheet(this->labelStyleSheet);

    this->ageLineEdit = new QLineEdit();
    this->ageLineEdit->setFixedHeight(appHeight*0.03);
    this->ageLineEdit->setFont(*this->caracterFontStyle);
    this->ageLineEdit->setStyleSheet(this->labelStyleSheet);

    this->idNumberEdit = new QLineEdit();
    this->idNumberEdit->setFixedHeight(appHeight*0.03);
    this->idNumberEdit->setFont(*this->caracterFontStyle);
    this->idNumberEdit->setStyleSheet(this->labelStyleSheet);

    this->marryLineEdit = new QLineEdit();
    this->marryLineEdit->setFixedHeight(appHeight*0.03);
    this->marryLineEdit->setFont(*this->caracterFontStyle);
    this->marryLineEdit->setStyleSheet(this->labelStyleSheet);

    this->nationLineEdit = new QLineEdit();
    this->nationLineEdit->setFixedHeight(appHeight*0.03);
    this->nationLineEdit->setFont(*this->caracterFontStyle);
    this->nationLineEdit->setStyleSheet(this->labelStyleSheet);

    this->professionalLineEdit = new QLineEdit();
    this->professionalLineEdit->setFixedHeight(appHeight*0.03);
    this->professionalLineEdit->setFont(*this->caracterFontStyle);
    this->professionalLineEdit->setStyleSheet(this->labelStyleSheet);

    this->leadDoctorEdit = new QLineEdit();
    this->leadDoctorEdit->setFixedHeight(appHeight*0.03);
    this->leadDoctorEdit->setFont(*this->caracterFontStyle);
    this->leadDoctorEdit->setStyleSheet(this->labelStyleSheet);

    this->therapyTimeEdit = new QLineEdit();
    this->therapyTimeEdit->setFixedHeight(appHeight*0.03);
    this->therapyTimeEdit->setFont(*this->caracterFontStyle);
    this->therapyTimeEdit->setStyleSheet(this->labelStyleSheet);

    this->drugAllergyLineEdit = new QLineEdit();
    this->drugAllergyLineEdit->setFixedHeight(appHeight*0.03);
    this->drugAllergyLineEdit->setFont(*this->caracterFontStyle);
    this->drugAllergyLineEdit->setStyleSheet(this->labelStyleSheet);

    this->remarksLineEdit = new QLineEdit();
    this->remarksLineEdit->setFixedHeight(appHeight*0.03);
    this->remarksLineEdit->setFont(*this->caracterFontStyle);
    this->remarksLineEdit->setStyleSheet(this->labelStyleSheet);

    this->patientInfoContainer = new QWidget();
    this->patientInfoContainer->setStyleSheet("border: 0px solid white;background-color:transparent");
    this->patientInfoContainer->setFixedHeight(appHeight*0.28);
    this->patientInfoContainerLayout = new QGridLayout(patientInfoContainer);
    this->patientInfoContainerLayout->addWidget(nameLabel, 1, 0);
    this->patientInfoContainerLayout->addWidget(nameLineEdit, 1, 1);
    this->patientInfoContainerLayout->addWidget(birthdayLabel, 1, 2);
    this->patientInfoContainerLayout->addWidget(birthdayLineEdit, 1, 3);
    this->patientInfoContainerLayout->addWidget(sexualLabel, 2, 0);
    this->patientInfoContainerLayout->addWidget(sexualLineEdit, 2, 1);
    this->patientInfoContainerLayout->addWidget(ageLabel, 2, 2);
    this->patientInfoContainerLayout->addWidget(ageLineEdit, 2, 3);
    this->patientInfoContainerLayout->addWidget(idNumberLabel, 3, 0);
    this->patientInfoContainerLayout->addWidget(idNumberEdit, 3, 1);
    this->patientInfoContainerLayout->addWidget(marryLabel, 3, 2);
    this->patientInfoContainerLayout->addWidget(marryLineEdit, 3, 3);
    this->patientInfoContainerLayout->addWidget(nationLabel, 4, 0);
    this->patientInfoContainerLayout->addWidget(nationLineEdit, 4, 1);
    this->patientInfoContainerLayout->addWidget(professionalLabel, 4, 2);
    this->patientInfoContainerLayout->addWidget(professionalLineEdit, 4, 3);
    this->patientInfoContainerLayout->addWidget(leadDoctorLabel, 5, 0);
    this->patientInfoContainerLayout->addWidget(leadDoctorEdit, 5, 1);
    this->patientInfoContainerLayout->addWidget(therapyTimeLabel, 5, 2);
    this->patientInfoContainerLayout->addWidget(therapyTimeEdit, 5, 3);
    this->patientInfoContainerLayout->addWidget(drugAllergyLabel, 6, 0);
    this->patientInfoContainerLayout->addWidget(drugAllergyLineEdit, 6, 1, 1, 3, Qt::AlignVCenter);
    this->patientInfoContainerLayout->addWidget(remarksLabel, 7, 0);
    this->patientInfoContainerLayout->addWidget(remarksLineEdit, 7, 1, 1, 3, Qt::AlignVCenter);
    this->patientInfoContainerLayout->setSpacing(0);
    this->patientInfoContainerLayout->setMargin(0);

    this->commentTextEdit = new QTextEdit();
    this->commentTextEdit->setFixedHeight(appHeight*0.64);
    this->commentTextEdit->setFont(*this->caracterStyle);
    this->commentTextEdit->setStyleSheet(this->textEditStyleSheet);

    this->personalInformation = new QWidget();
    this->personalInformation->setFixedWidth(this->appWidth*0.4);
    this->personalInformation->setStyleSheet("background-color:steelblue");
    this->personalInformationLayout = new QVBoxLayout(personalInformation);
    this->personalInformationLayout->addWidget(patientInfoContainer);
    this->personalInformationLayout->addWidget(commentTextEdit);
    this->personalInformationLayout->setSpacing(0);
    this->personalInformationLayout->setMargin(5);

    //! --------------------------------------------------------------------------------------
    //! the total information of patient and doctors
    //! --------------------------------------------------------------------------------------
    this->totalInformation = new QWidget();
    this->totalInformationLayout = new QHBoxLayout(this->totalInformation);
    this->totalInformationLayout->addWidget(patientsPhotoAndMedicaleImageContainerWidget);
    this->totalInformationLayout->addWidget(personalInformation);
    this->totalInformationLayout->setSpacing(0);
    this->totalInformationLayout->setMargin(0);

    //! --------------------------------------------------------------------------------------
    //! loading bar
    //! --------------------------------------------------------------------------------------
    this->surgeryLoadingBar = new QProgressBar();
    this->surgeryLoadingBar->setStyleSheet("QPrgressBar{background-color:steelblue}"
                                           "QProgressBar::chunk {background: qlineargradient(x1: 0, y1: 0.5, x2: 1, y2: 0.5, stop: 0 green, stop: 1 white);}");
    this->surgeryLoadingBar->setFixedSize(this->appWidth*0.6,this->appHeight*0.03);
    this->surgeryLoadingBar->setMaximum(100);
    this->surgeryLoadingBar->setMinimum(0);

    this->surgeryLoadingIndicationLabel = new QLabel("status bar");
    this->surgeryLoadingIndicationLabel->setStyleSheet("background-color:transparent");
    this->surgeryLoadingIndicationLabel->setFixedSize(this->appWidth*0.4,this->appHeight*0.03);

    this->surgeryLoadingWidget = new QWidget();
    this->surgeryLoadingWidget->setFixedHeight(this->appHeight*0.03);
    this->surgeryLoadingWidgetLayout = new QHBoxLayout(this->surgeryLoadingWidget);
    this->surgeryLoadingWidgetLayout->addWidget(this->surgeryLoadingBar);
    this->surgeryLoadingWidgetLayout->addWidget(this->surgeryLoadingIndicationLabel);
    this->surgeryLoadingWidgetLayout->setSpacing(0);
    this->surgeryLoadingWidgetLayout->setMargin(0);

    //!--------------------------------------------------------------------------------------
    //!the layout of patients widget
    //!--------------------------------------------------------------------------------------
    this->patientsWidgetLayout = new QVBoxLayout(this);
    this->patientsWidgetLayout->addWidget(this->patientsWidgetToolBar);
    this->patientsWidgetLayout->addWidget(this->totalInformation);
    this->patientsWidgetLayout->addWidget(this->surgeryLoadingWidget);
    this->patientsWidgetLayout->setSpacing(0);
    this->patientsWidgetLayout->setMargin(0);
}

//!----------------------------------------------------------------------------------------------------
//!
//! \brief PatientsWidget::addPatientToListWidget
//! \param patients
//!
void PatientsWidget::addPatientToWidget(QString path){
    QListWidgetItem *patientItem = new QListWidgetItem();
    patientItem->setIcon(QIcon(path));

}

//!----------------------------------------------------------------------------------------------------
//!
//! \brief PatientsWidget::keyPressEvent
//! \param event
//!
 void PatientsWidget::keyPressEvent(QKeyEvent *event){
     switch(event->key()){
        case Qt::Key_Left:
            this->doLeftSelect();
            break;
        case Qt::Key_Right:
            this->doRightSelect();
            break;
     }
 }

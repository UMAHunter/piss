#include "GuidewareTrackingWindow.h"


/**
 * @brief GuidewareTrackingWindow::GuidewareTrackingWindow
 * @param rect
 * @param systemDispatcher
 * @param globalWorkSpaceColor
 */
GuidewareTrackingWindow::GuidewareTrackingWindow(QRect rect,
                                                 SystemDispatcher* systemDispatcher,
                                                 QString globalWorkSpaceColor) : QWidget(){

    this->x = rect.x();
    this->y = rect.y();
    this->width = rect.width();
    this->height = rect.height();
    this->systemDispatcher = systemDispatcher;
    this->globalWorkSpaceColor = globalWorkSpaceColor;

    this->initVariable();
    this->constructionIHM();
    this->setConnections();
    this->drawBackground();
}

//!----------------------------------------------------------------------------------------------------
//!
//! \brief GuidewareTrackingWindow::~GuidewareTrackingWindow
//!
GuidewareTrackingWindow::~GuidewareTrackingWindow(){

}

//!----------------------------------------------------------------------------------------------------
//!
//! \brief GuidewareTrackingWindow::setWorkSpaceColor
//! \param workspaceColor
//!
void GuidewareTrackingWindow::setWorkSpaceColor(QString workspaceColor){
    QColor *qworkspaceColor = new QColor(workspaceColor);

    this->workspaceRed   = qworkspaceColor->red();
    this->workspaceGreen = qworkspaceColor->green();
    this->workspaceBlue  = qworkspaceColor->blue();

    this->renderer->SetBackground((1.0*workspaceRed)/255, (1.0*workspaceGreen)/255, (1.0*workspaceBlue)/255);
}

//!----------------------------------------------------------------------------------------------------
//!
//! \brief GuidewareTrackingWindow::update
//!
void GuidewareTrackingWindow::update(){

    //! lecture dcm ct img
    vtkSmartPointer<vtkPNGReader> reader =vtkSmartPointer<vtkPNGReader>::New();
    QString dir = "C:\\Users\\wangtseng\\Documents\\CanalyserWorkspace\\CanalyserImageCenter\\guideware_tracking\\PNG\\";
    QDirIterator it(dir, QStringList() << "*.png", QDir::Files, QDirIterator::Subdirectories);
    while (it.hasNext()){
        BidimensionnelImage *imgPackage1 = new BidimensionnelImage();
        //qDebug() << it.next();
        reader->SetFileName (it.next().toLocal8Bit().data());
        reader->Update();
        imgPackage1->setImage(reader->GetOutput());
        imgPackage1->setTimeStamp(12345678);
        this->patientHandling->pushCTImage(imgPackage1);
    }

    //! show patient infomation
    this->surgeryIDLineEdit->setText(QString::number(this->patientHandling->getIdNumber(), 10));
    this->patientNameLineEdit->setText(this->patientHandling->getName());
    // this->surgeryDateLineEdit->setText(this->patientHandling->);

    //! display c-arm img
    this->VTKFlowDisplay();

    //! display on the left top window
    //this->GuidewireAndVesselMergeDisplay(this->patientHandling->fetchLatestCTImageForDisplay());
    //this->GuidewireAndVesselMergeDisplay(this->patientHandling->fetchLatestCTImageForDisplay()->getImage());
    this->displayTaskTimer->start(50);

}

//!
//! \brief GuidewareTrackingWindow::closeSystem
//!
void GuidewareTrackingWindow::closeSystem(){
    if (!(QMessageBox::information(this,tr("Guidewire Tracking View"),tr("Do you really want to log out Guidewire Tracking View?"),tr("Yes"),tr("No"))))
        this->close();
}

//!
//! \brief GuidewareTrackingWindow::updateLastFrame
//!
void GuidewareTrackingWindow::updateLastFrame(){

    if (this->patientHandling->getCTImageSequenceLength() > 0){
        //qDebug()<<"GuidewareTrackingWindow::updateLastFrame()"<<this->patientHandling->getCTImageSequenceLength();
        this->GuidewireAndVesselMergeDisplay(this->patientHandling->fetchLatestCTImageForDisplay());
    }
    else{
        //qDebug()<<"No more image";
    }
}

//!
//! \brief GuidewareTrackingWindow::GuidewireAndVesselMergeDisplay
//! \param input
//!
void GuidewareTrackingWindow::GuidewireAndVesselMergeDisplay(QImage input){
    guidewareTrackingDisplayVTK->clear();

    guidewareTrackingDisplayVTK->setPixmap(QPixmap::fromImage(input));

}


//!----------------------------------------------------------------------------------------------------
//!
//! \brief GuidewareTrackingWindow::setPatientHandling
//! \param patientHandling
//!
void GuidewareTrackingWindow::setPatientHandling(Patient *patientHandling){
    this->patientHandling = patientHandling;
}

//!----------------------------------------------------------------------------------------------------
//!
//! \brief GuidewareTrackingWindow::displayWindow
//!
void GuidewareTrackingWindow::displayWindow(){
    this->resize(this->width, this->height);
    this->move(this->x, this->y);
    this->show();
}

//!
//! \brief GuidewareTrackingWindow::initVariable
//!
void GuidewareTrackingWindow::initVariable(){
    this->setWindowFlags(Qt::FramelessWindowHint | Qt::WindowSystemMenuHint);// | Qt::WindowStaysOnTopHint);
    this->setWindowOpacity(1);
    this->setMouseTracking(true);
    this->setAutoFillBackground(true);

    this->caracterStyle = new QFont("Segoe UI", 8, QFont::AnyStyle, false);
    this->windowStyleSheet = "border: 1px solid aliceBlue;border-radius: 0px;padding: 2 2px;background-color: transparent; color: AliceBlue";
    this->displayTaskTimer = new QTimer();

    reader = vtkSmartPointer<vtkOBJReader>::New();
    mapper = vtkSmartPointer<vtkPolyDataMapper>::New();
    actor =  vtkSmartPointer<vtkActor>::New();
    renderer = vtkSmartPointer<vtkRenderer>::New();
    renderWindow = vtkSmartPointer<vtkRenderWindow>::New();
}

//!
//! \brief GuidewareTrackingWindow::setConnections
//!
void GuidewareTrackingWindow::setConnections(){
    this->connect(closeButton, SIGNAL(clicked()), this, SLOT(closeSystem()));
    this->connect(playButton, SIGNAL(clicked()), this, SLOT(realTimeVideoPlay()));
    this->connect(noVolumeButton, SIGNAL(clicked()), this, SLOT(lastFramePlay()));
    this->connect(screenShotButton, SIGNAL(clicked()), this, SLOT(screenShot()));
    this->connect(this->displayTaskTimer, SIGNAL(timeout()), this, SLOT(updateLastFrame()));
}

//!
//! \brief GuidewareTrackingWindow::VTKFlowDisplay
//!
void GuidewareTrackingWindow::VTKFlowDisplay(){

    QString humaBodyDataPath = this->systemDispatcher->getImageCenterPath()+"carm.obj";

    reader->SetFileName(humaBodyDataPath.toLocal8Bit().data());
    reader->Update();

    mapper->SetInputConnection(reader->GetOutputPort());
    actor->SetMapper(mapper);
    renderer->AddActor(actor);
    renderWindow->AddRenderer(renderer);
    CarmStructureDisplay->SetRenderWindow(renderWindow);

    renderer->ResetCamera();
    renderWindow->Render();
    CarmStructureDisplay->update();
}

//!--------------------------------------------------------------------------------------------------------------------------------
//!
//! \brief GuidewareTrackingWindow::screenShot
//!
void GuidewareTrackingWindow::screenShot(){
    QPixmap pixmap;
    QPixmap pix;

    //pix = pixmap.grabWidget(guidewareTrackingDisplayVTK, 0, 0, -1, -1);
    pix = pixmap.grabWindow(this->winId(), width*0.2,height*0.04, width*0.4,height*0.48);
    if(pix.isNull()){
        QMessageBox::information(this,"error","grab Screen failed",QMessageBox::Ok);
    }
    else{
        if(pix.save( "E:\\1.bmp", "BMP" )==false){
            QMessageBox::information(this,"right","save error",QMessageBox::Ok);
        }
        else{
            QMessageBox::information(this,"Grab","bitmap saved as E:\\1.bmp",QMessageBox::Ok);
        }
    }
}

//!--------------------------------------------------------------------------------------------------------------------------------
//!
//! \brief GuidewareTrackingWindow::realTimeVideoPlay
//!
void GuidewareTrackingWindow::realTimeVideoPlay(){
    realTimeVideoWidget->show();
    realTimeplayer->play();
}

//!--------------------------------------------------------------------------------------------------------------------------------
//!
//! \brief GuidewareTrackingWindow::lastFramePlay
//!
void GuidewareTrackingWindow::lastFramePlay(){
    lastFrameVideoWidget->show();
    lastFrameplayer->play();
}

//!--------------------------------------------------------------------------------------------------------------------------------
//!
//! \brief GuidewareTrackingWindow::drawBackground
//!
void GuidewareTrackingWindow::drawBackground(){
    this->setStyleSheet("background:"+this->globalWorkSpaceColor);

    setWorkSpaceColor(this->globalWorkSpaceColor);
}

//!--------------------------------------------------------------------------------------------------------------------------------
//!
//! \brief GuidewareTrackingWindow::testVtkwidget
//!
void GuidewareTrackingWindow::testVtkwidget(){

}

//!--------------------------------------------------------------------------------------------------------------------------------
//!
//! \brief GuidewareTrackingWindow::constructionIHM
//!
void GuidewareTrackingWindow::constructionIHM(){
    //!----------------------------------------------------------------------------------------------------
    //! name bar:display name of this window
    //!----------------------------------------------------------------------------------------------------
    this->nameBar = new QLabel();
    this->nameBar->setText("Guideware Tracking Window");
    this->nameBar->setFixedSize(width*0.20,height*0.04);
    this->nameBar->setStyleSheet("QWidget{background-color:transparent; color: Aliceblue; border: 0px solid gainsboro;border-bottom-width:1px solid gainsboro;border-right-width:1px solid gainsboro; border-radius: 0px;margin-top: 0ex;} ");
    this->nameBar->setFont(QFont("Segoe UI", 11, QFont::DemiBold, true));
    this->nameBar->setAlignment(Qt::AlignCenter);

    //!----------------------------------------------------------------------------------------------------
    //! vtk display bar:display name of VTKImage
    //!----------------------------------------------------------------------------------------------------
    this->vtkDisplayBar = new QWidget();
    this->vtkDisplayBar->setFixedSize(width*0.80,height*0.04);
    this->vtkDisplayBar->setStyleSheet("QWidget{background-color:transparent; color: Aliceblue; border: 0px solid gainsboro; border-bottom-width:1px solid gainsboro; border-radius: 0px;margin-top: 0ex;} ");

    //!----------------------------------------------------------------------------------------------------
    //! surgery information:including surgerID,patientName,surgeryDate
    //!----------------------------------------------------------------------------------------------------
    this->surgeryID = new QLabel();
    this->surgeryID = new QLabel("surgeryID:");
    this->surgeryID->setFont(*this->caracterStyle);
    this->surgeryID->setStyleSheet("border: 0px solid aliceBlue;border-radius: 0px;padding: 2 2px;background-color: transparent; color: AliceBlue");

    this->patientName = new QLabel();
    this->patientName = new QLabel("patientName:");
    this->patientName->setFont(*this->caracterStyle);
    this->patientName->setStyleSheet("border: 0px solid aliceBlue;border-radius: 0px;padding: 2 2px;background-color: transparent; color: AliceBlue");

    this->surgeryDate = new QLabel();
    this->surgeryDate = new QLabel("surgeryDate:");
    this->surgeryDate->setFont(*this->caracterStyle);
    this->surgeryDate->setStyleSheet("border: 0px solid aliceBlue;border-radius: 0px;padding: 2 2px;background-color: transparent; color: AliceBlue");

    this->surgeryIDLineEdit = new QLineEdit();
    this->surgeryIDLineEdit->setFont(QFont("Segoe UI", 8, QFont::AnyStyle, true));
    this->surgeryIDLineEdit->setReadOnly(true);
    this->surgeryIDLineEdit->setStyleSheet("QLineEdit {background-color:transparent; color:AliceBlue; border: 1px solid Gray;border-radius: 0px;padding: 0 8px; selection-background-color: darkAliceBlue;}");

    this->patientNameLineEdit = new QLineEdit();
    this->patientNameLineEdit->setFont(QFont("Segoe UI", 8, QFont::AnyStyle, true));
    this->patientNameLineEdit->setReadOnly(true);
    this->patientNameLineEdit->setStyleSheet("QLineEdit {background-color:transparent; color:AliceBlue; border: 1px solid Gray;border-radius: 0px;padding: 0 8px; selection-background-color: darkAliceBlue;}");

    this->surgeryDateLineEdit = new QLineEdit();
    this->surgeryDateLineEdit->setFont(QFont("Segoe UI", 8, QFont::AnyStyle, true));
    this->surgeryDateLineEdit->setReadOnly(true);
    this->surgeryDateLineEdit->setStyleSheet("QLineEdit {background-color:transparent; color:AliceBlue; border: 1px solid Gray;border-radius: 0px;padding: 0 8px; selection-background-color: darkAliceBlue;}");

    this->surgeryInformation = new QWidget();
    this->surgeryInformation->setFixedHeight(height*0.16);
    this->surgeryInformation->setStyleSheet("QWidget{background-color:transparent; color: Aliceblue; border: 0px solid gray; border-radius: 5px;margin-top: 1ex;} ");
    //this->surgeryInformation->setStyleSheet(this->windowStyleSheet);
    this->surgeryInformationLayout = new QGridLayout(this->surgeryInformation);
    this->surgeryInformationLayout->addWidget(surgeryID, 0, 0);
    this->surgeryInformationLayout->addWidget(surgeryIDLineEdit, 0, 1);
    this->surgeryInformationLayout->addWidget(patientName, 1, 0);
    this->surgeryInformationLayout->addWidget(patientNameLineEdit, 1, 1);
    this->surgeryInformationLayout->addWidget(surgeryDate, 2, 0);
    this->surgeryInformationLayout->addWidget(surgeryDateLineEdit, 2, 1);
    //this->surgeryInformationLayout->setMargin(0);
    //this->surgeryInformationLayout->setSpacing();

    //!----------------------------------------------------------------------------------------------------
    //! control button area
    //!----------------------------------------------------------------------------------------------------
    this->closeButton = new QPushButton();
    this->closeButton->setFixedSize(width*0.2*0.25,width*0.2*0.25);
    this->closeButton->setIcon(QIcon(":/images/shutdown.png"));
    this->closeButton->setIconSize(QSize(width*0.2*0.15,width*0.2*0.15));
    this->closeButton->setStyleSheet("QPushButton{background-color:transparent; color: Aliceblue; border: 0px solid gray; border-radius: 5px;margin-top: 1ex;} ");
//    this->closeButton->setStyleSheet("QPushButton{border-image: url(:/images/close.png);}"
//                                      "QPushButton:pressed{border-image: url(:/images/close_clicked.png);}");

    this->playButton = new QPushButton();
    this->playButton->setFixedSize(width*0.2*0.25,width*0.2*0.25);
    this->playButton->setIcon(QIcon(":/images/play.png"));
    this->playButton->setIconSize(QSize(width*0.2*0.15,width*0.2*0.15));
    this->playButton->setStyleSheet("background-color:transparent; color: Aliceblue; border: 0px solid gray; border-radius: 5px;margin-top: 1ex;");
//    this->unknownButton1->setStyleSheet("QPushButton{border-image: url(:/images/begin_therapy.png);}"
//                                      "QPushButton:hover{border-image: url(:/images/begin_therapy_hovering.png);}"
//                                      "QPushButton:pressed{border-image: url(:/images/begin_therapy_clicked.png);}");

    this->zoomInButton = new QPushButton();
    this->zoomInButton->setFixedSize(width*0.2*0.25,width*0.2*0.25);
    this->zoomInButton->setIcon(QIcon(":/images/zoom_in.png"));
    this->zoomInButton->setIconSize(QSize(width*0.2*0.17,width*0.2*0.17));
    this->zoomInButton->setStyleSheet("background-color:transparent; color: Aliceblue; border: 0px solid gray; border-radius: 5px;margin-top: 1ex; ");
    //this->zoomInButton->setStyleSheet("QPushButton{border-image: url(:/images/zoom_in.png);}");

    this->zoomOutButton = new QPushButton();
    this->zoomOutButton->setFixedSize(width*0.2*0.25,width*0.2*0.25);
    this->zoomOutButton->setIcon(QIcon(":/images/zoom_out.png"));
    this->zoomOutButton->setIconSize(QSize(width*0.2*0.15,width*0.2*0.15));
    this->zoomOutButton->setStyleSheet("background-color:transparent; color: Aliceblue; border: 0px solid gray; border-radius: 5px;margin-top: 1ex; ");
    //this->zoomOutButton->setStyleSheet("QPushButton{border-image: url(:/images/zoom_out.png);}");

    this->screenShotButton = new QPushButton();
    this->screenShotButton->setFixedSize(width*0.2*0.25,width*0.2*0.25);
    this->screenShotButton->setIcon(QIcon(":/images/printscreen.png"));
    this->screenShotButton->setIconSize(QSize(width*0.2*0.15,width*0.2*0.15));
    this->screenShotButton->setStyleSheet("background-color:transparent; color: Aliceblue; border: 0px solid gray; border-radius: 5px;margin-top: 1ex; ");

    this->measureButton = new QPushButton();
    this->measureButton->setFixedSize(width*0.2*0.25,width*0.2*0.25);
    this->measureButton->setIcon(QIcon(":/images/measure.png"));
    this->measureButton->setIconSize(QSize(width*0.2*0.15,width*0.2*0.15));
    this->measureButton->setStyleSheet("background-color:transparent; color: Aliceblue; border: 0px solid gray; border-radius: 5px;margin-top: 1ex; ");

    this->noVolumeButton = new QPushButton();
    this->noVolumeButton->setFixedSize(width*0.2*0.25,width*0.2*0.25);
    this->noVolumeButton->setIcon(QIcon(":/images/no_volume.png"));
    this->noVolumeButton->setIconSize(QSize(width*0.2*0.15,width*0.2*0.15));
    this->noVolumeButton->setStyleSheet("background-color:transparent; color: Aliceblue; border: 0px solid gray; border-radius: 5px;margin-top: 1ex; ");

    this->settingButton = new QPushButton();
    this->settingButton->setFixedSize(width*0.2*0.25,width*0.2*0.25);
    this->settingButton->setIcon(QIcon(":/images/setting.png"));
    this->settingButton->setIconSize(QSize(width*0.2*0.15,width*0.2*0.15));
    this->settingButton->setStyleSheet("background-color:transparent; color: Aliceblue; border: 0px solid gray; border-radius: 5px;margin-top: 1ex; ");

    this->recordButton = new QPushButton();
    this->recordButton->setFixedSize(width*0.2*0.25,width*0.2*0.25);
    this->recordButton->setIcon(QIcon(":/images/recording.png"));
    this->recordButton->setIconSize(QSize(width*0.2*0.15,width*0.2*0.15));
    this->recordButton->setStyleSheet("QPushButton{background-color:transparent; color: Aliceblue; border: 0px solid gray; border-radius: 5px;margin-top: 1ex;}");

    this->resetButton = new QPushButton();
    this->resetButton->setFixedSize(width*0.2*0.25,width*0.2*0.25);
    this->resetButton->setIcon(QIcon(":/images/reset.png"));
    this->resetButton->setIconSize(QSize(width*0.2*0.15,width*0.2*0.15));
    this->resetButton->setStyleSheet("background-color:transparent; color: Aliceblue; border: 0px solid gray; border-radius: 5px;margin-top: 1ex; ");

    this->fullButton = new QPushButton();
    this->fullButton->setFixedSize(width*0.2*0.25,width*0.2*0.25);
    this->fullButton->setIcon(QIcon(":/images/full.png"));
    this->fullButton->setIconSize(QSize(width*0.2*0.15,width*0.2*0.15));
    this->fullButton->setStyleSheet("background-color:transparent; color: Aliceblue; border: 0px solid gray; border-radius: 5px;margin-top: 1ex; ");

    this->undoButton = new QPushButton();
    this->undoButton->setFixedSize(width*0.2*0.25,width*0.2*0.25);
    this->undoButton->setIcon(QIcon(":/images/undo.png"));
    this->undoButton->setIconSize(QSize(width*0.2*0.15,width*0.2*0.15));
    this->undoButton->setStyleSheet("background-color:transparent; color: Aliceblue; border: 0px solid gray; border-radius: 5px;margin-top: 1ex; ");

    this->leftTurnButton = new QPushButton();
    this->leftTurnButton->setFixedSize(width*0.2*0.25,width*0.2*0.25);
    this->leftTurnButton->setIcon(QIcon(":/images/turnleft.png"));
    this->leftTurnButton->setIconSize(QSize(width*0.2*0.15,width*0.2*0.15));
    this->leftTurnButton->setStyleSheet("background-color:transparent; color: Aliceblue; border: 0px solid gray; border-radius: 5px;margin-top: 1ex; ");

    this->rightTurnButton = new QPushButton();
    this->rightTurnButton->setFixedSize(width*0.2*0.25,width*0.2*0.25);
    this->rightTurnButton->setIcon(QIcon(":/images/turnright.png"));
    this->rightTurnButton->setIconSize(QSize(width*0.2*0.15,width*0.2*0.15));
    this->rightTurnButton->setStyleSheet("background-color:transparent; color: Aliceblue; border: 0px solid gray; border-radius: 5px;margin-top: 1ex; ");

    this->showVesselButton = new QPushButton();
    this->showVesselButton->setFixedSize(width*0.2*0.25,width*0.2*0.25);
    this->showVesselButton->setIcon(QIcon(":/images/vessel.png"));
    this->showVesselButton->setIconSize(QSize(width*0.2*0.15,width*0.2*0.15));
    this->showVesselButton->setStyleSheet("background-color:transparent; color: Aliceblue; border: 0px solid gray; border-radius: 5px;margin-top: 1ex; ");

    this->showGuidewireLocation = new QPushButton();
    this->showGuidewireLocation->setFixedSize(width*0.2*0.25,width*0.2*0.25);
    this->showGuidewireLocation->setIcon(QIcon(":/images/location.png"));
    this->showGuidewireLocation->setIconSize(QSize(width*0.2*0.15,width*0.2*0.15));
    this->showGuidewireLocation->setStyleSheet("background-color:transparent; color: Aliceblue; border: 0px solid gray; border-radius: 5px;margin-top: 1ex; ");

    this->controlButtonArea = new QWidget();
    this->controlButtonArea->setFixedHeight(width*0.2);
    this->controlButtonArea->setStyleSheet("QWidget{background-color:transparent; color: Aliceblue; border: 1px solid gainsboro; border-radius: 5px;margin-top: 1ex; margin-right: 1ex;} ");
    this->controlButtonAreaLayout = new QGridLayout(this->controlButtonArea);
    this->controlButtonAreaLayout->addWidget(this->closeButton, 0, 0);
    this->controlButtonAreaLayout->addWidget(this->playButton, 0, 1);
    this->controlButtonAreaLayout->addWidget(this->zoomInButton, 0, 2);
    this->controlButtonAreaLayout->addWidget(this->zoomOutButton, 0, 3);
    this->controlButtonAreaLayout->addWidget(this->screenShotButton, 1, 0);
    this->controlButtonAreaLayout->addWidget(this->measureButton, 1, 1);
    this->controlButtonAreaLayout->addWidget(this->noVolumeButton, 1, 2);
    this->controlButtonAreaLayout->addWidget(this->settingButton, 1, 3);
    this->controlButtonAreaLayout->addWidget(this->recordButton, 2, 0);
    this->controlButtonAreaLayout->addWidget(this->resetButton, 2, 1);
    this->controlButtonAreaLayout->addWidget(this->fullButton, 2, 2);
    this->controlButtonAreaLayout->addWidget(this->undoButton, 2, 3);
    this->controlButtonAreaLayout->addWidget(this->leftTurnButton, 3, 0);
    this->controlButtonAreaLayout->addWidget(this->rightTurnButton, 3, 1);
    this->controlButtonAreaLayout->addWidget(this->showVesselButton, 3, 2);
    this->controlButtonAreaLayout->addWidget(this->showGuidewireLocation, 3, 3);

    this->controlButtonAreaLayout->setMargin(5);
    this->controlButtonAreaLayout->setSpacing(0);

    //!----------------------------------------------------------------------------------------------------
    //! unknown area
    //!----------------------------------------------------------------------------------------------------
    this->unknownArea = new QWidget();
    this->unknownArea->setStyleSheet("QWidget{background-color:transparent; color: Aliceblue; border: 0px solid gray; border-radius: 5px;margin-top: 1ex;} ");

    //!----------------------------------------------------------------------------------------------------
    //!guideControlBoard:including guideControlBoard,controlButtonArea,unknownArea
    //!----------------------------------------------------------------------------------------------------
    this->guideControlBoard = new QWidget();
    this->guideControlBoard->setFixedWidth(width*0.2);
    this->guideControlBoard->setStyleSheet("QWidget{background-color:transparent; color: Aliceblue; border: 0px solid gainsboro; border-right-width:1px solid gainsboro; border-radius: 0px;margin-top: 0ex;} ");
    //this->guideControlBoard->setStyleSheet(this->windowStyleSheet);
    this->guideControlBoardLayout = new QVBoxLayout(this->guideControlBoard);
    this->guideControlBoardLayout->addWidget(this->surgeryInformation);
    this->guideControlBoardLayout->addWidget(this->controlButtonArea);
    this->guideControlBoardLayout->addWidget(this->unknownArea);
    this->guideControlBoardLayout->setMargin(0);
    this->guideControlBoardLayout->setSpacing(0);

    //!----------------------------------------------------------------------------------------------------
    //!realTimeDisplay
    //!----------------------------------------------------------------------------------------------------
    realTimeDisplay = new QWidget();
    realTimeVideoWidget = new QVideoWidget;
    realTimeplayer = new QMediaPlayer;
    realTimePlayList = new QMediaPlaylist;
    realTimeDisplayLayout = new QHBoxLayout(realTimeDisplay);

    realTimeDisplay->setFixedSize(width*0.40,height*0.48);
    realTimeVideoWidget->setFixedSize(width*0.40,height*0.48);
    realTimeDisplayLayout->addWidget(realTimeVideoWidget);
    realTimeDisplayLayout->setMargin(0);
    realTimePlayList->addMedia(QUrl::fromLocalFile("C:\\Users\\wangtseng\\Documents\\CanalyserWorkspace\\CanalyserImageCenter\\guideware_tracking\\LIU_XINKUN-3-3.avi"));
    realTimePlayList->setCurrentIndex(1);
    realTimePlayList->setPlaybackMode(QMediaPlaylist::CurrentItemInLoop);
    realTimeplayer->setPlaylist(realTimePlayList);
    realTimeplayer->setVideoOutput(realTimeVideoWidget);

    //!----------------------------------------------------------------------------------------------------
    //!lastFrameWidget
    //!----------------------------------------------------------------------------------------------------
    lastFrameWidget = new QWidget();
    lastFrameVideoWidget = new QVideoWidget;
    lastFrameplayer = new QMediaPlayer;
    lastFramePlayList = new QMediaPlaylist;
    lastFrameLayout = new QHBoxLayout(lastFrameWidget);

    lastFrameWidget->setFixedSize(width*0.40,height*0.48);
    lastFrameVideoWidget->setFixedSize(width*0.40,height*0.48);
    lastFrameLayout->addWidget(lastFrameVideoWidget);
    lastFrameLayout->setMargin(0);
    lastFramePlayList->addMedia(QUrl::fromLocalFile("C:\\Users\\wangtseng\\Documents\\CanalyserWorkspace\\CanalyserImageCenter\\guideware_tracking\\LIU_XINKUN-51-51.avi"));
    lastFramePlayList->setCurrentIndex(1);
    lastFramePlayList->setPlaybackMode(QMediaPlaylist::CurrentItemInLoop);
    lastFrameplayer->setPlaylist(lastFramePlayList);
    lastFrameplayer->setVideoOutput(lastFrameVideoWidget);

    //!----------------------------------------------------------------------------------------------------
    //!guideware tracking display
    //!----------------------------------------------------------------------------------------------------
    guidewareTrackingDisplay = new QWidget();
    guidewareTrackingDisplay->setFixedSize(width*0.40,height*0.48);
    guidewareTrackingDisplayLayout = new QHBoxLayout(guidewareTrackingDisplay);
    guidewareTrackingDisplayVTK = new QLabel();
    guidewareTrackingDisplayVTK->setFixedSize(width*0.40,height*0.48);
    guidewareTrackingDisplayVTK->setStyleSheet("background-color:58.0/255, 89.0/255, 92.0/255");
    guidewareTrackingDisplayLayout->addWidget(guidewareTrackingDisplayVTK);
    guidewareTrackingDisplayLayout->setMargin(0);


    //!----------------------------------------------------------------------------------------------------
    //!somethingElse
    //!----------------------------------------------------------------------------------------------------
    CarmStructureWidget = new QWidget();
    CarmStructureWidget->setFixedSize(width*0.40,height*0.48);
    CarmStructureLayout = new QHBoxLayout(CarmStructureWidget);
    CarmStructureDisplay = new QVTKWidget();
    CarmStructureDisplay->setFixedSize(width*0.40,height*0.48);
    CarmStructureDisplay->setStyleSheet("background-color:red");
    CarmStructureLayout->addWidget(CarmStructureDisplay);
    CarmStructureDisplay->show();
    CarmStructureLayout->setMargin(0);

    //!----------------------------------------------------------------------------------------------------
    //!vtkDisplayBoard:including realTimeDisplay,lastFrameWidget,guidewareTrackingDisplay,somethingElse
    //!----------------------------------------------------------------------------------------------------
    this->vtkDisplayBoard = new QWidget();
    this->vtkDisplayBoard->setFixedSize(width*0.80,height*0.96);
    //this->vtkDisplayBoard->setStyleSheet("QWidget{background-color:transparent; color: Aliceblue; border: 0px solid gainsboro; border-radius: 0px;margin-top: 0ex;} ");
    this->vtkDisplayBoardLayout = new QGridLayout(this->vtkDisplayBoard);
    this->vtkDisplayBoardLayout->addWidget(realTimeDisplay, 0, 0);
    this->vtkDisplayBoardLayout->addWidget(lastFrameWidget, 0, 1);
    this->vtkDisplayBoardLayout->addWidget(guidewareTrackingDisplay, 1, 0);
    this->vtkDisplayBoardLayout->addWidget(CarmStructureWidget, 1, 1);
    this->vtkDisplayBoardLayout->setMargin(0);
    this->vtkDisplayBoardLayout->setSpacing(5);

    //!----------------------------------------------------------------------------------------------------
    //!main window
    //!----------------------------------------------------------------------------------------------------
    this->guidewareTrackingLayout = new QGridLayout(this);
    this->guidewareTrackingLayout->addWidget(this->nameBar, 0, 0);
    this->guidewareTrackingLayout->addWidget(this->vtkDisplayBar, 0, 1);
    this->guidewareTrackingLayout->addWidget(this->guideControlBoard, 1, 0);
    this->guidewareTrackingLayout->addWidget(this->vtkDisplayBoard, 1, 1);
    this->guidewareTrackingLayout->setMargin(0);
    this->guidewareTrackingLayout->setSpacing(0);

}

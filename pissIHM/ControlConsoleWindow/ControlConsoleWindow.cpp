#include "ControlConsoleWindow.h"

ControlConsoleWindow::ControlConsoleWindow(QRect rect,
                                           QTime* surgeryTime,
                                           SystemDispatcher* systemDispatcher,
                                           AlgorithmTestPlatform *algorithmTestPlatform) : QWidget()
{
    this->width = rect.width();
    this->height = rect.height();


    this->initVariable();
    this->constructionIHM();
    this->setConnections();
    this->drawBackground();
}

void ControlConsoleWindow::initVariable(){
    this->setWindowFlags(Qt::FramelessWindowHint | Qt::WindowSystemMenuHint | Qt::WindowStaysOnTopHint);
}

void ControlConsoleWindow::displayWindow(){
    this->showFullScreen();
}

void ControlConsoleWindow::constructionIHM(){

    realTimeTrackingWindow = new QFrame();

    indicationWindow = new QFrame();
    indicationWindow->setFixedHeight(this->height*0.05);

    guidewareTrackingIndication = new QLabel("Guideware's movement");
    guidewareTrackingIndication->setFixedSize(this->width*0.47, this->height*0.05);

    ballonStentTranckingArea = new QLabel("ballon/Stent's Movement");
    ballonStentTranckingArea->setFixedSize(this->width*0.47, this->height*0.05);

    missionAccomplishimentButton = new QPushButton("A");
    missionAccomplishimentButton->setFixedSize(this->width*0.06, this->height*0.05);

    indicationWindowLayout = new QHBoxLayout(indicationWindow);
    indicationWindowLayout->addWidget(guidewareTrackingIndication);
    indicationWindowLayout->addWidget(missionAccomplishimentButton);
    indicationWindowLayout->addWidget(ballonStentTranckingArea);
    indicationWindowLayout->setSpacing(0);
    indicationWindowLayout->setMargin(0);

    controlConsoleWindowLayout = new QVBoxLayout(this);
    controlConsoleWindowLayout->addWidget(realTimeTrackingWindow);
    controlConsoleWindowLayout->addWidget(indicationWindow);
    controlConsoleWindowLayout->setSpacing(0);
    controlConsoleWindowLayout->setMargin(0);

}

void ControlConsoleWindow::setConnections(){
    this->connect(missionAccomplishimentButton, SIGNAL(clicked()), this, SLOT(onMissionAccomplishimentButtonClicked()));
}

void ControlConsoleWindow::onMissionAccomplishimentButtonClicked(){
    if (!(QMessageBox::information(this,tr("Igss Surgery"),tr("Do you really want to terminate the surgery?"),tr("Yes"),tr("No")))){
        qDebug()<<"onMissionAccomplishimentButtonClicked";
        emit missionAccomplishiment();
    }
}

void ControlConsoleWindow::drawBackground(){
    pixmap = new QPixmap(":/images/background_darkBlue.png");
    QPalette p =  this->palette();

    p.setBrush(QPalette::Background, QBrush(pixmap->scaled(QSize(this->width, this->height), Qt::IgnoreAspectRatio, Qt::SmoothTransformation)));

    this->setPalette(p);
    this->setMask(pixmap->mask());
}

#include "PatientItem.h"

PatientItem::PatientItem(int appWidth, int appHeight)
{
    this->appWidth = appWidth;
    this->appHeight = appHeight;

    this->consructIHM();
}

void PatientItem::consructIHM(){

    this->photoLabelStyleSheet = "border: 0px solid aliceBlue;border-radius: 0px;padding: 2 2px;background-color: transparent; color: AliceBlue";
    this->labelStyleSheet = "border: 0.5px solid aliceBlue;border-radius: 0px;padding: 2 2px;background-color: transparent; color: AliceBlue";

    this->patientInfoOne = new QLabel();
    this->patientInfoOne->setStyleSheet("border-image: url(:/images/Brain.png)");
    this->patientInfoTwo = new QLabel();
    this->patientInfoTwo->setStyleSheet("border-image: url(:/images/xueguan.png)");
    this->patientInfoThree = new QLabel();
    this->patientInfoThree->setStyleSheet("border-image: url(:/images/notebook.png)");

    this->patientInfoWidget = new QWidget();
    this->patientInfoWidget->setFixedHeight(this->appHeight*0.028);
    this->patientInfoLayout = new QHBoxLayout(patientInfoWidget);
    this->patientInfoLayout->addWidget(patientInfoOne);
    this->patientInfoLayout->addWidget(patientInfoTwo);
    this->patientInfoLayout->addWidget(patientInfoThree);
    this->patientInfoLayout->setSpacing(0);
    this->patientInfoLayout->setMargin(0);

    this->patientNameLabel = new QLabel();
    this->patientNameLabel->setFixedHeight(this->appHeight*0.166*0.16);
    this->patientNameLabel->setStyleSheet("background-color: rgba(0, 0, 0, 100);");
    this->patientNameLabel->setAlignment(Qt::AlignCenter);
    this->patientPhotoBlankArea = new QWidget();

    this->patientPhotoLabel = new QLabel();
    this->patientPhotoLabel->setStyleSheet(this->photoLabelStyleSheet);
    this->patientPhotoLayout = new QVBoxLayout(patientPhotoLabel);
    this->patientPhotoLayout->addWidget(patientNameLabel);
    this->patientPhotoLayout->addWidget(patientPhotoBlankArea);
    this->patientPhotoLayout->setSpacing(0);
    this->patientPhotoLayout->setMargin(0);

    this->patientItemLayout = new QVBoxLayout(this);
    this->patientItemLayout->addWidget(patientPhotoLabel);
    this->patientItemLayout->addWidget(patientInfoWidget);
    this->patientItemLayout->setSpacing(0);
    this->patientItemLayout->setMargin(0);
}

QLabel* PatientItem::getPatientPhoto(){
    return this->patientPhotoLabel;
}
QLabel* PatientItem::getPatientName(){
    return this->patientNameLabel;
}

PatientItem::~PatientItem()
{

}


#ifndef PATIENTSWIDGET_H
#define PATIENTSWIDGET_H

#include <QWidget>
#include <QObject>
#include <QListWidget>
#include <QVBoxLayout>
#include <Patients.h>
#include <QDebug>
#include <QTextEdit>
#include <AlgorithmTestPlatform.h>
#include <QPushButton>
#include <QLabel>
#include <QLineEdit>
#include <QTime>
#include <QMouseEvent>
#include <QColor>
#include <QPalette>
#include <QBrush>
#include <QPixmap>
#include <QBitmap>
#include <QProgressDialog>
#include <QSpinBox>

#include "SystemDispatcher.h"
#include "DicomCDRomReader.h"
#include "SurgeryPlanWindow.h"
#include "GuidewareTrackingWindow.h"
#include "PatientInformationWidget.h"
#include "ControlConsoleWindow.h"
#include "PatientItem.h"
#include "SuperviseWindow.h"
#include "Patient.h"
#include "vtkPiecewiseFunction.h"
#include "vtkColorTransferFunction.h"
#include "PlottingBoard.h"

/**
 * @brief The PatientsWidget class
 */
class PatientsWidget : public QWidget
{
    Q_OBJECT
public:
    PatientsWidget(int screen_count,
                   SystemDispatcher* dispatcher,
                   AlgorithmTestPlatform *algorithmTestPlatform,
                   PatientInformationWidget* patientInformationWidget,
                   QTime* surgeryTimer,
                   QFont *caracterStyle,
                   int appWidth,
                   int appHeight,
                   QString workspaceColor,
                   QString globalFontColor);

    void drawBackground(QWidget *widget, QString path, int w, int h);
    void setSurgeryPlanWindow(SurgeryPlanWindow* surgeryPlanWindow);
    void setGuidewareTrackingWindow(GuidewareTrackingWindow* guidewareTrackingWindow);
    void setControlConsoleWindow(ControlConsoleWindow * controlConsoleWindow);
    void terminateSurgery();

    void initVariable();
    void constructIHM();

    void findPatientExisted();
    void setConnections();
    void addPatientToWidget(QString path);
    void displayLastFiveOrLess();
    void keyPressEvent(QKeyEvent *event);
    void displayCurrentPatinetInfo();
    void displayBrainSegImage();
    void display(vtkImageData *imgToBeDisplayed);
    void setPatientHandling(Patient *patientHandling);
    void setWorkSpaceColor(QString workspaceColor);

    bool loadMRAImageFile(const QString &fileName);
    void update();

    int testX();
    int testY();

private:

    int flyThroughCpt;

    CenterLineReader centerLineReader;

    QTimer *flyThroughTimer;

    vtkPoints *vessel;
    int vesselPointCount;
    vtkImageData* currentVolumeImage;

    QString workspaceColor;
    QString globalFontColor;

    int workspaceRed;
    int workspaceGreen;
    int workspaceBlue;

    ControlConsoleWindow * controlConsoleWindow;
    SystemDispatcher* dispatcher;
    SuperviseWindow *superviseWindow;
    Patient* patientHandling;

    vtkFixedPointVolumeRayCastMapper *volumeMapper;
    vtkVolumeRayCastCompositeFunction  *compositeFunction;
    vtkVolume *volume;
    vtkSmartPointer<vtkRenderWindow> renderWindow;
    vtkSmartPointer<vtkRenderer> renderer;
    vtkVolumeProperty*volumeProperty;

    QVBoxLayout* patientsWidgetLayout;
    QGridLayout* patientsWidgetWorkspaceLayout;
    QHBoxLayout* patientsPhotoWidgetLayout;
    QVBoxLayout* waittingPatientsAndBlackAreaWindowLayout;
    QHBoxLayout* waittingPatientPhotoesLayout;
    QVBoxLayout* patientHandlingWidgetLayout;
    QHBoxLayout* patientsWidgetToolBarLayout;
    QGridLayout* patientInfoContainerLayout;
    QVBoxLayout* firstPatientPhotoWidgetLayout;
    QVBoxLayout* secondPatientPhotoWidgetLayout;
    QVBoxLayout* thirdPatientPhotoWidgetLayout;
    QVBoxLayout* fourthPatientPhotoWidgetLayout;
    QHBoxLayout *surgeryLoadingWidgetLayout;

    QWidget* patientsWidgetToolBar;
    QLabel* patientsPhotoWidget;

    QLabel *patientImageDispalyArea;
    QLabel *imageConfigurationArea;

    QPushButton *guidewareMovementButton;

    QSpacerItem *imageConfigurationAreaSpacer;

    QHBoxLayout *imageConfigurationAreaLayout;

    QVBoxLayout *patientImageDispalyAreaLayout;

    QVTKWidget* patientImageLoaded;

    QWidget*medicalImageAnalyseArea;
    QHBoxLayout *medicalImageAnalyseAreaLayout;

    QWidget* patientsWidgetWorkspace;

    QWidget* patientHandlingWidget;
    QWidget* upBlackArea;
    QWidget* waittingPatientPhotoes;
    QWidget* downBlackArea;
    QWidget* leftBlackArea;
    QWidget* rightBlackArea;
    QLabel* patientInfoContainer;
    QWidget* surgeryLoadingWidget;

    PatientItem* firstPatientPhotoWidget;
    PatientItem* secondPatientPhotoWidget;
    PatientItem* thirdPatientPhotoWidget;
    PatientItem* fourthPatientPhotoWidget;

    QProgressBar* surgeryLoadingBar;

    QLabel*surgeryLoadingIndicationLabel;
    QLabel*currentPatientPhoto;
    QVBoxLayout*currentPatientPhotoLayout;
    QLabel*currentPatientInfo;
    QWidget *patientPhotoBlankArea;


    PlottingBoard *plottingBoard;
    QLabel *plottingBoardIndication;
    QLabel *plottingBoardConfiguration;
    QHBoxLayout *plottingBoardConfigurationLayout;
    QLabel* volumeDataAnalyseArea;
    QVBoxLayout *volumeDataAnalyseAreaLayout;

    QPushButton* plottingButton;
    QSpacerItem* plottingBoardConfigurationSpacer;

    QLabel* nameLabel;
    QLabel* birthdayLabel;
    QLabel* sexualLabel;
    QLabel* ageLabel;
    QLabel* idNumberLabel;
    QLabel* marryLabel;
    QLabel* nationLabel;
    QLabel* professionalLabel;
    QLabel* drugAllergyLabel;
    QLabel* remarksLabel;
    QLabel* leadDoctorLabel;
    QLabel* therapyTimeLabel;

    QLabel *curvePlanReformationArea;
    QLabel *flyThroughtArea;
    QVBoxLayout *flyThroughtAreaLayout;
    QLabel *flyThroughtConfigurationBar;
    QHBoxLayout *flyThroughtConfigurationBarLayout;
    QVTKWidget *flyThroughDisplayArea;
    QSpacerItem* flyThroughtConfigurationBarSpacer;

    QPushButton *cutButton;
    QSpinBox *cuttingLayerOption;

    QLabel *analyseResultDisplayArea;
    QVBoxLayout *analyseResultDisplayAreaLayout;

    QLineEdit* nameLineEdit;
    QLineEdit* birthdayLineEdit;
    QLineEdit* sexualLineEdit;
    QLineEdit* ageLineEdit;
    QLineEdit* idNumberEdit;
    QLineEdit* marryLineEdit;
    QLineEdit* nationLineEdit;
    QLineEdit* professionalLineEdit;
    QLineEdit* drugAllergyLineEdit;
    QLineEdit* remarksLineEdit;
    QLineEdit * leadDoctorEdit;
    QLineEdit* therapyTimeEdit;

    QFont *caracterStyle;
    QFont *caracterFontStyle;

    QWidget* waittingPatientsAndBlackAreaWindow;

    QPushButton* leftSelectButton;
    QPushButton* rightSelectButton;
    QPushButton* cdRomParseButton;
    QPushButton* addPatientButton;
    QPushButton* surgeryLaunchButton;
    QPushButton* patientsWidgetConfigurationButton;
    QPushButton* simpleModeButton;

    AlgorithmTestPlatform *algorithmTestPlatform;

    SurgeryPlanWindow* surgeryPlanWindow;
    GuidewareTrackingWindow* guidewareTrackingWindow;
    PatientInformationWidget* patientInformationWidget;


    QSpacerItem* controlBarSpacer;
    //QSpacerItem* patientInfoContainerSpacer;

    DicomCDRomReader *dicomCDRomReader;

    QList<QLabel*> waitingPatientsQueue;
    QList<QLabel*> waitingPatientsNameQueue;
    QStringList currentPatinetInfoQueue;

    QStringList waitingPatientsPhotoStringQueue;
    QStringList waitingPatientsStringNameQueue;
    QStringList waitingPatientsIDQueue;
    QStringList waitingPatientsMraPathQueue;

    int appWidth;
    int appHeight;
    int numberOfPatient;
    bool surgeryLaunched;
    bool surgeryTerminated;
    int screen_count;

    QString labelStyleSheet;
    QString photoLabelStyleSheet;
    QString textEditStyleSheet;
    QTime* surgeryTimer;

signals:
    void surgeryLaunchButtonCicked();

public slots:
    void doParseCdRom();
    void launchSurgery();
    //void terminateSurgery();
    void addPatient();
    void doLeftSelect();
    void doRightSelect();
    void onPlottingButtonClicked();
    void onGuidewareMovementButtonClicked();
    void flyThrough();
    void onCutButtonClicked();
};

#endif // PATIENTSWIDGET_H

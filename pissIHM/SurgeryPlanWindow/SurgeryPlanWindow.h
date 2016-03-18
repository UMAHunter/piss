#ifndef SURGERYPLANWINDOW_H
#define SURGERYPLANWINDOW_H

//#include "CenterLineProcess.h"

#include <QWidget>
#include <QFrame>
#include <QSplitter>
#include <QGridLayout>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QDebug>
#include <QPushButton>
#include <QLabel>
#include <QLineEdit>
#include <QFileInfo>
#include <QDir>
#include <QGroupBox>
#include <QCheckBox>
#include <QRadioButton>
#include <QLCDNumber>
#include <QTime>
#include <QDateTime>
#include <QVector>
#include <QFile>
#include <QByteArray>
#include <QString>
#include <QStringList>
#include <QPoint>
#include <QMenu>
#include <QAction>
#include <QCursor>

//! VTK - auto initialization
#include <vtkAutoInit.h>
VTK_MODULE_INIT(vtkRenderingOpenGL)
VTK_MODULE_INIT(vtkInteractionStyle)
VTK_MODULE_INIT(vtkRenderingFreeType)
VTK_MODULE_INIT(vtkRenderingFreeTypeOpenGL)
VTK_MODULE_INIT(vtkRenderingVolumeOpenGL)

#include <vtkSmartPointer.h>
#include <vtkSphereSource.h>
#include <vtkPolyDataMapper.h>
#include <vtkActor.h>
#include <vtkImageViewer.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkInteractorStyleImage.h>
#include <vtkRenderer.h>
#include <vtkJPEGReader.h>
#include <vtkMetaImageReader.h>
#include <vtkImageViewer2.h>
#include <vtkVolumeRayCastCompositeFunction.h>
#include <vtkVolumeRayCastMapper.h>
#include <vtkPiecewiseFunction.h>
#include <vtkColorTransferFunction.h>
#include <vtkVolumeProperty.h>
#include <vtkDataSet.h>
#include <vtkPointData.h>
#include <vtkDataArray.h>
#include <QVTKWidget.h>
#include <vtkImageData.h>
#include <vtkDataSetMapper.h>
#include <vtkUnstructuredGrid.h>
#include <vtkPolyVertex.h>
#include <vtkPoints.h>
#include <vtkProperty.h>

#include <vtkOBJReader.h>
#include <vtkOrientationMarkerWidget.h>
#include <vtkFixedPointVolumeRayCastMapper.h>
#include <vtkSplineDrivenImageSlicer.h>
#include <Patient.h>
#include <CPushButton.h>
#include <PlottingBoard.h>
#include <PatientWidgetConfigurationBoard.h>
#include <ColorChooseWindow.h>
#include <vtkEventQtSlotConnect.h>
#include <SystemDispatcher.h>
#include <vtkImageAppend.h>
#include "CurveReformationWindow.h"
#include "AlgorithmTestPlatform.h"
#include "CenterLinePoint.h"
#include "CenterLineReader.h"
#include <vtkSCurveSpline.h>
#include <vtkParametricFunctionSource.h>
#include <vtkParametricSpline.h>
#include "vtkDataSetMapper.h"
#include <vtkSCurveSpline.h>
#include <vtkParametricSpline.h>
#include <vtkCamera.h>

struct TransferOptionStates{
    bool opacityTransferOptionChoosen = false;
    bool colorTransferOptionChoosen = false;
    bool gradientTransferOptionChoosen = false;
};

struct TransferCurveIndex{
    int opacityTransferCurveIndex;
    int colorTransferCurveIndex;
    int gradientTransferCurveIndex;
};

struct ImageOptionStates{
    bool originalOptionState;
    bool transparentBrainOptionState;
    bool greyMatterOptionState;
    bool whiteMatterOptionState;
    bool vesselOptionState;
    bool interventionalRouteOptionState;
};

class SurgeryPlanWindow : public QWidget
{
    Q_OBJECT
public:
    explicit SurgeryPlanWindow(QRect rect,
                               QTime* surgeryTime,
                               SystemDispatcher* systemDispatcher,
                               AlgorithmTestPlatform *algorithmTestPlatform);
    void displayWindow();

    void createRandomVtkImageData();
    void display(vtkImageData *imgToBeDisplayed);
    void displayBrainandPath(vtkImageData *imgToBeDisplayed,QString referencePath);
    void displaySize();
    void setPatientHandling(Patient *patientHandling);
    void update();
    void loadVesselsExisted();
    void setStartTime(int start_time);

protected:
    vtkEventQtSlotConnect* MraConnections;

private:
    QString vesselHandlingName;
    QRect rect;
    int start_time;
    int current_time;
    QTime* surgeryTime;

    QTimer *timer;

    AlgorithmTestPlatform *algorithmTestPlatform;

    double transformationPlottingBoard_AbscissaValue;
    double transformationPlottingBoard_OrdinateValue;
    bool transformationPlottingBoard_Clicked;
    int lockingTransformationPointIndex;

    ColorChooseWindow* colorChooseWindow;

    PatientWidgetConfigurationBoard *patientWidgetConfigurationBoard;

    //MedicalImageHandler *medicalImageHandler;
    QString mraImagefilePath;

    QPixmap *pixmap;

    QFrame *controlBar;
    QHBoxLayout *controlBarLayout;

    CPushButton *imageConfigurationButton;
    CPushButton *imageUpdateButton;
    CPushButton *curveReformationButton;

    CurveReformationWindow* curveReformationWindow;

    CPushButton *beginTherapyButton;
    QSpacerItem *spacer_controlbar;

    //! patient's information widget
    QFrame *patientInformationWidget;
    QVBoxLayout *patientInformationLayout;

    QFrame *patientTitleBar;
    QHBoxLayout *patientTitleBarLayout;
    QWidget *briefWidget;
    QLabel *patientTitleLabel;
    QLabel *photoWidget;
    QSpacerItem *spacer_1;
    QSpacerItem *spacer_2;



    QFrame *patientClinicalWidgetsContainer;
    QHBoxLayout *patientClinicalWidgetsContainerLayout;
    QWidget *patientMRAImageOptionWidget;
    QVBoxLayout *patientMRAImageOptionWidgetLayout;

    QWidget *patientImageInformationWidget;
    QHBoxLayout* patientImageInformationWidgetLayout;
    QLabel* surgeryPlanWindowLabel;
    QLCDNumber *elapsedTimeLabel;
    //QPushButton* sugeryEndnessButton;

    QGroupBox * histogramGroupBox;
    QVBoxLayout *histogramGroupBoxLayout;
    QWidget *imageStatisticsWidget;
    QGridLayout *imageStatisticsWidgetLayout;

    QLabel *grayscaleValueNumberLabel;
    QLabel *grayscaleValueMeanLabel;
    QLabel *grayscaleValueMedianLabel;
    QLabel *grayscaleValueStandardDeviationLabel;
    QLabel *grayscaleValueMaximumValueLabel;
    QLabel *grayscaleValueMinimumValueLabel;

    QLineEdit *grayscaleValueNumberLineEdit;
    QLineEdit *grayscaleValueMeanLineEdit;
    QLineEdit *grayscaleValueMedianLineEdit;
    QLineEdit *grayscaleValueStandardDeviationLineEdit;
    QLineEdit *grayscaleValueMaximumValueLineEdit;
    QLineEdit *grayscaleValueMinimumValueLineEdit;

    PlottingBoard *histogramPlottingBoard;

    QGroupBox * volumeRenderingGroupBox;
    QVBoxLayout *volumeRenderingGroupBoxLayout;
    QWidget *transferChoicesWidget;
    QHBoxLayout *transferChoicesLayout;
    QLabel *transferChoiceLabel;
    QRadioButton *opacityTransferChoice;
    QRadioButton *colorTransferChoice;
    QRadioButton *gradientTransferChoice;
    QSpacerItem *transferChoicesWidgetSpacer;

    PlottingBoard *transformationPlottingBoard;

    QWidget *transformationIndicationBar;
    QHBoxLayout *transformationIndicationBarLayout;
    QLabel *currentGrayScaleValueLabel;
    QLabel *currentTransformationValueLabel;
    CPushButton *transformationButton;
    QLineEdit *currentGrayScaleValueLineEdit;
    QLineEdit *currentTransformationValueLineEdit;


    QSpacerItem *patientMRAImageOptionWidgetSpacer;

    QWidget *patientMRAImageConfigurationWidget;
    QVBoxLayout *patientMRAImageConfigurationWidgetLayout;
    QWidget *patientMRAImageOption;
    QHBoxLayout *patientMRAImageOptionLayout;

    CPushButton *originalOption;
    CPushButton *transparentBrainOption;
    CPushButton *greyMatterOption;
    CPushButton *whiteMatterOption;
    CPushButton *vesselOption;
    CPushButton *interventionalRouteOption;
    QPushButton *quitSurgeryPlanButton;

    ImageOptionStates imageOptionStates;

    QLabel *patientMRAImageOptionLabel;

    QWidget *patientMRAImageWidget;
    QHBoxLayout *patientMRAImageWidgetLayout;


    QVTKWidget *patientMRAImage;

    QWidget *patientMRAImageManipulation;


    vtkActor *actorreferencePath;//...
    vtkDataSetMapper *mapperreferencePath;
    vtkUnstructuredGrid *grid;
    vtkPolyVertex *poly;
    vtkPoints *points;

    vtkFixedPointVolumeRayCastMapper *volumeMapper;
    vtkVolumeRayCastCompositeFunction  *compositeFunction;
    vtkVolume *volume;
    vtkSmartPointer<vtkRenderWindow> renderWindow;
    vtkSmartPointer<vtkRenderer> renderer;

    vtkPiecewiseFunction*opacityTransferFunction;
    vtkPiecewiseFunction *gradientTransferFunction;
    vtkColorTransferFunction *colorTransferFunction;
    vtkVolumeProperty*volumeProperty;

    //vtkRenderWindowInteractor * iren;
    vtkInteractorStyleTrackballCamera *style;
    //vtkMyCallback *callBack;

    TransferOptionStates transferOptionStates;
    TransferCurveIndex transferCurveIndex;

    // cpr information widget
    QFrame *cprAnalyseWidget;
    QHBoxLayout *cprAnalyseWidgetLayout;
    QTreeWidget *centerlineTreeWidget;
    QTreeWidgetItem *vesselsFolder;
    QIcon *defaultFolderIcon;
    QIcon *fileUnloadedIcon;
    QIcon *fileLoadedIcon;
    QIcon *defaultTitleIcon;
    QFont *font;

    //.............
    QVTKWidget *centerLineVTKWidget;
    vtkPoints *singleVesselPoints;
    //vtkDataSetMapper *

    //.............
    QVTKWidget *cprOutcomingVTKWidget;
    vtkPolyDataMapper *cprmapper;
    vtkFixedPointVolumeRayCastMapper *cprmapper1;
    vtkActor *cpractor;
    vtkSCurveSpline *xSpline;
    vtkSCurveSpline *ySpline;
    vtkSCurveSpline *zSpline;
    vtkParametricSpline *spline;
    vtkParametricFunctionSource *functionSource;
    vtkSplineDrivenImageSlicer *reslicer;
    vtkImageAppend *append;


    vtkImageShiftScale *m_pShift;
    vtkPlane *pPlane;
    vtkCutter *pCut;

    vtkColorTransferFunction *cprcolorTranFun;
    vtkPiecewiseFunction *cprPieceFun;
    vtkVolumeProperty *cprVolumeproperty;
    vtkVolume *cprvolume;
    vtkRenderer *cprRenderer;
    vtkRenderWindow *cprRenderwindow;


    QWidget *flyThroughWidget;
    QVBoxLayout *mainLayout;
    Patient *patientHandling;

    vtkImageData *enhancedImage = NULL;

    int x;
    int y;
    int appWidth;
    int appHeight;
    SystemDispatcher* systemDispatcher;




    void constructPatientInformationWidget();
    void constructCprAnalyseWidget();
    void constructControlBar();
    void initialisation();
    void regroupAllComponents();
    void setConnections();
    void drawBackground();
    void initVariable();

    void updatePatientPersonelInformation();
    void updatePatientPersonelPhoto();

    void displayVesselse();
    void displayCpr();
    void displayCenterLine();
    void displayPatientMRAImage();
    void updatePatientMRAImageStatistics();
    void updatePatientMRAImageHistogram();
    void updatePatientMRAImageTransformationCurves();
    void removeCurveBy(int index);
    void updatePatientMRAImage();
    void generateNewOpacityPoint(double abscissa, double ordinate);
    void generateNewColorPoints(double abscissa, double ordinate);
    void generateNewGradientPoint(double abscissa, double ordinate);
    void generateInitColorPoints(double abscissa, int colorCount);
    void initialRendering();
    void opacityPointTracking();
    void colorPointTracking();
    void gradientPointTracking();
    //void calculateCenterOfTheVolume();
    void sfunctionSource();
    void cprMath();

signals:
    void finished();
    void error(QString err);

public slots:
    void process();
    void opacityTransformationStateChanged(bool state);
    void colorTransformationStateChanged(bool state);
    void gradientTransformationStateChanged(bool state);
    void generateNewTransformationPoint(QMouseEvent* event);
    void transformPointTracking(QMouseEvent* event);
    void lockTargetPoint(QMouseEvent* event);
    void positioningTransformPoint(QMouseEvent* event);
    void updateCoords(vtkObject* obj);

    void originalOptionHovered();
    void originalOptionClicked();
    void originalOptionReleased();
    void originalOptionLeaved();

    void transparentBrainOptionHovered();
    void transparentBrainOptionClicked();
    void transparentBrainOptionReleased();
    void transparentBrainOptionLeaved();

    void greyMatterOptionHovered();
    void greyMatterOptionClicked();
    void greyMatterOptionReleased();
    void greyMatterOptionLeaved();

    void whiteMatterOptionHovered();
    void whiteMatterOptionClicked();
    void whiteMatterOptionReleased();
    void whiteMatterOptionLeaved();

    void vesselOptionHovered();
    void vesselOptionClicked();
    void vesselOptionReleased();
    void vesselOptionLeaved();

    void interventionalRouteOptionHovered();
    void interventionalRouteOptionClicked();
    void interventionalRouteOptionReleased();
    void interventionalRouteOptionLeaved();

    void displayConfigurationBoard();
    void getVesselEnhancedImage();
    void stopSurgery();

    void displayCurveReformatwionWindow();
    void closeSurgeryPlanWindow();

    void showTime();
    void showContextMenu(const QPoint &pos);
    void loadVesselAction();
    void unloadVesselAction();
    void deleteVesselAction();


signals:



};

#endif // SURGERYPLANWINDOW_H

#ifndef GUIDEWARETRACKINGWINDOW_H
#define GUIDEWARETRACKINGWINDOW_H

#include <Patient.h>
#include <SystemDispatcher.h>
#include <QGridLayout>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QPushButton>
#include <QLabel>
#include <QWidget>
#include <QPixmap>
#include <QPalette>
#include <QBrush>
#include <QBitmap>
#include <QVTKWidget.h>
#include <QMediaPlayer>
#include <QMediaPlaylist>
#include <QVideoWidget>
#include <QImage>
#include <QMessageBox>
#include <QLineEdit>
#include <QTimer>
#include <QDirIterator>
#include <QColor>

#include <vtkBMPReader.h>
#include <vtkOBJReader.h>
#include <vtkSmartPointer.h>
#include <vtkImageViewer2.h>
#include <vtkDICOMImageReader.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkRenderer.h>
#include <vtkImageCanvasSource2D.h>
#include <vtkSphereSource.h>
#include <vtkSmartPointer.h>
#include <vtkPolyDataMapper.h>
#include <Patient.h>
#include <vtkPNGReader.h>
#include <BidimensionnelImage.h>


/**
 * @brief The GuidewareTrackingWindow class
 */
class GuidewareTrackingWindow : public QWidget
{
    Q_OBJECT
public:
    explicit GuidewareTrackingWindow(QRect rect,
                                     SystemDispatcher* systemDispatcher,
                                     QString globalWorkSpaceColor);
    ~GuidewareTrackingWindow();

    void setWorkSpaceColor(QString workspaceColor);
    void initVariable();
    void displayWindow();
    void constructionIHM();
    void setConnections();
    void drawBackground();
    void testVtkwidget();
    void GuidewireAndVesselMergeDisplay( QImage input);
    void VTKFlowDisplay();
    void setPatientHandling(Patient *patientHandling);
    void update();

private:
    QString globalWorkSpaceColor;
    int workspaceRed;
    int workspaceGreen;
    int workspaceBlue;

    QTimer *displayTaskTimer;

    int x;
    int y;
    int width;
    int height;
    Patient* patientHandling;
    SystemDispatcher* systemDispatcher;

    QFont *caracterStyle;
    QString windowStyleSheet;

    QPixmap *pixmap;

    QGridLayout* guidewareTrackingLayout;
    QGridLayout* vtkDisplayBoardLayout;
    QVBoxLayout* guideControlBoardLayout;
    QGridLayout* surgeryInformationLayout;
    QGridLayout* controlButtonAreaLayout;

    QPushButton* closeButton;
    QPushButton* playButton;
    QPushButton* noVolumeButton;
    QPushButton* screenShotButton;
    QPushButton* zoomInButton;
    QPushButton* zoomOutButton;
    QPushButton* measureButton;
    QPushButton* settingButton;
    QPushButton* recordButton;
    QPushButton* resetButton;
    QPushButton* fullButton;
    QPushButton* undoButton;
    QPushButton* leftTurnButton;
    QPushButton* rightTurnButton;
    QPushButton* showVesselButton;
    QPushButton* showGuidewireLocation;

    QWidget* vtkDisplayBar;
    QWidget* guideControlBoard;
    QWidget* vtkDisplayBoard;
    QWidget* realTimeDisplay;
    QWidget* lastFrameWidget;
    QWidget* guidewareTrackingDisplay;
    QWidget* CarmStructureWidget;
    QWidget* surgeryInformation;
    QWidget* controlButtonArea;
    QWidget* unknownArea;

    QLabel* guidewareTrackingDisplayVTK;
    QVTKWidget* CarmStructureDisplay;

    QHBoxLayout* realTimeDisplayLayout;
    QHBoxLayout* lastFrameLayout;
    QHBoxLayout* guidewareTrackingDisplayLayout;
    QHBoxLayout* CarmStructureLayout;
    QHBoxLayout* r_layout;

    QLabel* nameBar;
    QLabel* surgeryID;
    QLabel* patientName;
    QLabel* surgeryDate;

    QLineEdit* surgeryIDLineEdit;
    QLineEdit* patientNameLineEdit;
    QLineEdit* surgeryDateLineEdit;

    QMediaPlayer* realTimeplayer;
    QMediaPlayer* lastFrameplayer;
    QMediaPlaylist* realTimePlayList;
    QMediaPlaylist* lastFramePlayList;

    QVideoWidget* realTimeVideoWidget;
    QVideoWidget* lastFrameVideoWidget;

    vtkSmartPointer<vtkOBJReader> reader;
    vtkSmartPointer<vtkPolyDataMapper> mapper;
    vtkSmartPointer<vtkActor> actor;
    vtkSmartPointer<vtkRenderer> renderer;
    vtkSmartPointer<vtkRenderWindow> renderWindow;


public slots:
    void closeSystem();
    void screenShot();
    void realTimeVideoPlay();
    void lastFramePlay();
    void updateLastFrame();
};

#endif // GUIDEWARETRACKINGWINDOW_H

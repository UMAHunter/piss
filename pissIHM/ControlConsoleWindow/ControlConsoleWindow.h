#ifndef CONTROLCONSOLEWINDOW_H
#define CONTROLCONSOLEWINDOW_H

#include <QWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPushButton>
#include <QLabel>
#include <QFrame>
#include <QPixmap>
#include <QBrush>
#include <QMessageBox>
#include <QBitmap>
#include "SystemDispatcher.h"
#include "AlgorithmTestPlatform.h"


class ControlConsoleWindow : public QWidget
{
    Q_OBJECT

private:
    QVBoxLayout *controlConsoleWindowLayout;
    QHBoxLayout* indicationWindowLayout;

    QLabel* guidewareTrackingIndication;
    QLabel* ballonStentTranckingArea;
    QPushButton* missionAccomplishimentButton;

    QFrame *realTimeTrackingWindow;
    QFrame *indicationWindow;

    int width;
    int height;
    QString workspaceColor;
    SystemDispatcher* systemDispatcher;
    AlgorithmTestPlatform *algorithmTestPlatform;
    QTime* surgeryTime;


public:
    explicit ControlConsoleWindow(QRect rect,
                                  QTime* surgeryTime,
                                  SystemDispatcher* systemDispatcher,
                                  AlgorithmTestPlatform *algorithmTestPlatform,
                                  QString workspaceColor);
    void initVariable();
    void displayWindow();
    void constructionIHM();
    void setConnections();
    void drawBackground();

signals:
    void missionAccomplishiment();

public slots:
    void onMissionAccomplishimentButtonClicked();
};

#endif // CONTROLCONSOLEWINDOW_H

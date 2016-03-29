#ifndef SURGERYSYSTEMWIDGET_H
#define SURGERYSYSTEMWIDGET_H

#include <QWidget>
#include <QFrame>
#include <QPushButton>
#include <QHBoxLayout>
#include <QSpacerItem>

#include "CommunicationStatesContainer.h"
#include "SystemComponentsContainer.h"
#include "SystemDispatcher.h"
#include "AlgorithmTestPlatform.h"


/**
 * @brief The SurgerySystemWidget class
 */
class SurgerySystemWidget:public QWidget
{
    Q_OBJECT
private:
    QWidget *surgerySystemControlBar;
    QWidget *surgerySystemComponents;

    QPushButton *startServerButton;
    QPushButton *stopServerButton;

    QSpacerItem *surgerySystemControlBarItem;

    QHBoxLayout *surgerySystemControlBarLayout;
    QVBoxLayout *myLayout;
    QHBoxLayout *surgerySystemComponentsLayout;
    SystemComponentsContainer *systemComponentsContainer;
    CommunicationStatesContainer *communicationStatesContainer;

    int width;
    int height;

    SystemDispatcher* systemDispatcher;
    AlgorithmTestPlatform* algorithmTestPlatform;

public:
    void initVariable();
    void constructIHM();
    void setConnections();
    void closeSystem();

public slots:
    void onStartServerButtonClicked();
    void onStopServerButtonClicked();

public:
     explicit SurgerySystemWidget(int width,
                                  int height,
                                  SystemDispatcher* systemDispatcher,
                                  AlgorithmTestPlatform* algorithmTestPlatform);
};

#endif // SURGERYSYSTEMWIDGET_H

#ifndef SURGERYSYSTEMWIDGET_H
#define SURGERYSYSTEMWIDGET_H

#include <QWidget>
#include <QFrame>
#include <QHBoxLayout>
#include "CommunicationStatesContainer.h"
#include "SystemComponentsContainer.h"


/**
 * @brief The SurgerySystemWidget class
 */
class SurgerySystemWidget:public QWidget
{
    Q_OBJECT
private:
    QWidget *surgerySystemControlBar;
    QWidget *surgerySystemComponents;

    QVBoxLayout *myLayout;
    QHBoxLayout *surgerySystemComponentsLayout;
    SystemComponentsContainer *systemComponentsContainer;
    CommunicationStatesContainer *communicationStatesContainer;

    int width;
    int height;

public:
    void initVariable();
    void constructIHM();
    void setConnections();

public:
     explicit SurgerySystemWidget(int width, int height);
};

#endif // SURGERYSYSTEMWIDGET_H

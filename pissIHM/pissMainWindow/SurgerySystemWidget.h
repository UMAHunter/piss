#ifndef SURGERYSYSTEMWIDGET_H
#define SURGERYSYSTEMWIDGET_H

#include <QWidget>
#include <QFrame>
#include <QHBoxLayout>


class SurgerySystemWidget:public QWidget
{
    Q_OBJECT
private:
    QWidget *surgerySystemControlBar;
    QWidget *surgerySystemComponents;

    QVBoxLayout *myLayout;
    QHBoxLayout *surgerySystemComponentsLayout;
    QFrame *systemComponentsContainer;
    QFrame *communicationStatesContainer;

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

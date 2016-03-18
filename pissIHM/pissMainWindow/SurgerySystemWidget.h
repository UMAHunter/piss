#ifndef SURGERYSYSTEMWIDGET_H
#define SURGERYSYSTEMWIDGET_H

#include <QWidget>
#include <QFrame>
#include <QHBoxLayout>


class SurgerySystemWidget:public QWidget
{
    Q_OBJECT
private:
    QVBoxLayout *surgerySystemWidgetLayout;
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

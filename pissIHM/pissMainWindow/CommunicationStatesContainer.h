#ifndef COMMUNICATIONSTATESCONTAINER_H
#define COMMUNICATIONSTATESCONTAINER_H

#include <QFrame>
#include <QVBoxLayout>
#include <QLabel>
#include <QTableWidget>
#include <QTreeWidget>
#include <QHeaderView>
#include <QGroupBox>
#include <PlottingBoard.h>

#include "Device.h"

/**
 * @brief The CommunicationStatesContainer class
 * @author cheng wang, fan de yuan
 */
class CommunicationStatesContainer : public QFrame
{
    Q_OBJECT

private:
    int width;
    int height;
    QStringList hardwareHeader;
    QStringList transmissionHeader;
    QString groupBoxStyleSheet;

    PlottingBoard *communicationFrameRateWindow;

    QWidget *CommunicationStatesContainerWidget;
    QWidget *communicationInformationWindow;
    QHBoxLayout *communicationInformationWindowLayout;

    QTableWidget *HardwareInformation;

    QGroupBox *transmissionArea;
    QGroupBox *receptionArea;

    QTreeWidget *transmissionBuffer;
    QTreeWidget *receptionBuffer;

    QVBoxLayout *CommunicationStatesContainerLayout;
    QHBoxLayout *transmissionAreaLayout;
    QHBoxLayout *receptionAreaLayout;

public:
    explicit CommunicationStatesContainer(int width, int height);
    void initVariable();
    void constructIHM();
    void setConnections();

    void setDeviceInfo(Device *device);

signals:

public slots:
};

#endif // COMMUNICATIONSTATESCONTAINER_H

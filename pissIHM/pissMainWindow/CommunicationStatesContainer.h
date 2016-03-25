#ifndef COMMUNICATIONSTATESCONTAINER_H
#define COMMUNICATIONSTATESCONTAINER_H

#include <QFrame>


/**
 * @brief The CommunicationStatesContainer class
 * @author fan de yuan
 */
class CommunicationStatesContainer : public QFrame
{
    Q_OBJECT

private:
    int width;
    int height;

public:
    explicit CommunicationStatesContainer(int width, int height);
    void initVariable();
    void constructIHM();
    void setConnections();

signals:

public slots:
};

#endif // COMMUNICATIONSTATESCONTAINER_H

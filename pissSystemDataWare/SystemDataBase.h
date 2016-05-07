#ifndef SYSTEMDATABASE_H
#define SYSTEMDATABASE_H

#include "Patients.h"
#include "SystemMetaData.h"
#include "ImageProcessingFactory.h"
#include "CArm.h"
#include "Devices.h"


class SystemDataBase{

public:
    SystemDataBase();

    void setPaths(QString workspace_path,  QString patients_path, QString metadata_path, QString image_center_path);

    QString getSystemWorkSpace();
    QString getPatientsPath();
    QString getMetaData();
    QString getImageCenterPath();

    int findPatientsExisted();
    Patients* getPatientsData();
    Patient* getPatientById(int id);
    QStringList getPatientsStatus();

    IgssImage* getPatientMRAImageById(int id);
    void setImageProcessingFactory(ImageProcessingFactory* imageProcessingFactory);

private:
    Patients* patients;
    SystemMetaData* metaData;
    CArm* carm;
    ImageProcessingFactory* imageProcessingFactory;

    Devices* devices;//setDevices.methode to be created..

};

#endif // SYSTEMDATABASE_H

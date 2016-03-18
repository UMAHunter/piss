#include "CenterLineReader.h"

CenterLineReader::CenterLineReader()
{

}

CenterLineReader::~CenterLineReader()
{

}

//! -------------------------------------------------------------------------------------------------
//!
//! \brief CenterLineReader::doReadCenterLineFile
//! \param centerlineFilePath
//!
void CenterLineReader::doReadCenterLineFile(QString centerlineFilePath, vtkPoints *vessel){

    QFile file(centerlineFilePath);
    if(!file.open(QIODevice::ReadOnly|QIODevice::Text)){
        qDebug()<<"sorry,can't open the file!"<<endl;
    }
    while(!file.atEnd()){
        QByteArray line=file.readLine();
        QString str(line);
        QStringList parame=str.split(" ");
        vessel->InsertNextPoint(parame[0].toDouble(0), parame[1].toDouble(0), parame[2].toDouble(0));
    }
}

//! -------------------------------------------------------------------------------------------------
//!
//! \brief CenterLineReader::centerLineFileDir
//! \param centerlinedirPath
//!
void CenterLineReader::doReadCenterlineFolder(QString centerlineFolderPath){
    QDir dir(centerlineFolderPath);
    if(!dir.exists())
    {
        return ;
    }
    QStringList filter;
    filter<<QString("*.txt");
    dir.setFilter(QDir::Files|QDir::NoSymLinks);
    dir.setNameFilters(filter);

    int dir_count = dir.count();
    if(dir_count < 0){
        return ;
    }

    QStringList string_list;
    QChar separator = QChar('/');
    if(centerlineFolderPath.contains(separator)){
        separator = QChar('\\');
    }
    QChar last_char = centerlineFolderPath.at(centerlineFolderPath.length()-1);
    if(last_char == separator ){
        separator = QChar();
    }

    int pointscount=0;
    for(int i=0; i<dir.count();i++){
        QString file_name = dir[i];
        QString file_path =centerlineFolderPath + separator + file_name;
        string_list.append(file_path);
       // qDebug()<<string_list.at(i);
        QFile file(string_list.at(i));
        if(!file.open(QIODevice::ReadOnly|QIODevice::Text)){
            qDebug()<<"sorry,can't open the file!"<<endl;
        }
        while(!file.atEnd()){
            QByteArray line=file.readLine();
            QString str(line);
            QStringList parame=str.split(" ");

            CenterLinePoint *p = new CenterLinePoint();
            p->set_abscissa(parame[0].toDouble(0));
            p->set_vertical(parame[1].toDouble(0));
            p->set_sagittal(parame[2].toDouble(0));//1.26
            //qDebug()<<parame[0].toDouble(0)<<parame[1].toDouble(0)<<parame[2].toDouble(0);
            vesselsPoints.append(p);
            pointscount++;
        }
    }
    qDebug()<<"The total reference files:"<<dir.count();
    qDebug()<<"The total centerline points:"<<pointscount;
}


//! -----------------------------------------------------------------------------------------------------------
//!
//! \brief CenterLineReader::get_vesselsPoints
//! \return
//!
QVector<CenterLinePoint*> CenterLineReader::get_vesselsPoints(){
     return this->vesselsPoints;
 }

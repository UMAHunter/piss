#ifndef IGSSSCUTTER_H
#define IGSSSCUTTER_H

#include "vtkPlane.h"
#include "vtkCutter.h"
#include "vtkActor.h"
#include "vtkImageShiftScale.h"
#include "vtkPolyDataMapper.h"

#include <QDebug>


class igsssCutter
{

private:
    vtkPlane *plane;
    vtkCutter *cutter;
    vtkPolyDataMapper *mapper;

public:
    vtkActor * cut(double* p0, double* p1, double* p2, vtkImageShiftScale* shiftScaleImageData);

public:
    igsssCutter();
};

#endif // IGSSSCUTTER_H

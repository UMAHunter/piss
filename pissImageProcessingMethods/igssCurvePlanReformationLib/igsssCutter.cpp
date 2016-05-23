#include "igsssCutter.h"


igsssCutter::igsssCutter()
{
    plane = vtkPlane::New();
    cutter = vtkCutter::New();
    mapper = vtkPolyDataMapper::New();
}

//! --------------------------------------------------------------------------------------------------------
//!
//! \brief cut
//! \param p0
//! \param p1
//! \param p2
//! \param shiftScaleImageData
//! \return
//!
vtkActor * igsssCutter::cut(double* p0, double* p1, double* p2, vtkImageShiftScale* shiftScaleImageData){

    vtkActor *ret = vtkActor::New();

    plane->SetOrigin(p1);
    plane->SetNormal((p2[0]-p0[0])/2,(p2[1]-p0[1])/2,(p2[2]-p0[2])/2);
    cutter->SetCutFunction(plane);
    cutter->SetInputConnection(shiftScaleImageData->GetOutputPort());
    cutter->Update();
    cutter->GenerateCutScalarsOff();
    mapper->SetInputData(cutter->GetOutput());
    mapper->Update();

    ret->SetMapper(mapper);

    return ret;
}

#include <VolumeRendering.h>

void MainWindow::volumerendering()
{
    QObject;

    //Read data
    vtkNew<vtkDICOMImageReader> dicomseriesreader2;
    QString path = lineedit->text();
    QByteArray ba = path.toLocal8Bit();
    const char* path_str = ba.data();
    dicomseriesreader2->SetDirectoryName(path_str);

    // Ray-cast mapper is needed to do the ray-casting
    vtkNew<vtkFixedPointVolumeRayCastMapper> volumeMapper;
    volumeMapper->SetInputConnection(dicomseriesreader2->GetOutputPort());

    vtkNew<vtkColorTransferFunction> volumeColor;
    volumeColor->AddRGBPoint(0, 0.0, 0.0, 0.0);
    volumeColor->AddRGBPoint(500, 240.0 / 255.0, 184.0 / 255.0, 160.0 / 255.0);
    volumeColor->AddRGBPoint(1000, 240.0 / 255.0, 184.0 / 255.0, 160.0 / 255.0);
    volumeColor->AddRGBPoint(1150, 1.0, 1.0, 240.0 / 255.0); // Ivory

    vtkNew<vtkPiecewiseFunction> volumeScalarOpacity;
    volumeScalarOpacity->AddPoint(0, 0.00);
    volumeScalarOpacity->AddPoint(500, 0.15);
    volumeScalarOpacity->AddPoint(1000, 0.15);
    volumeScalarOpacity->AddPoint(1150, 0.85);

    vtkNew<vtkPiecewiseFunction> volumeGradientOpacity;
    volumeGradientOpacity->AddPoint(0, 0.0);
    volumeGradientOpacity->AddPoint(90, 0.5);
    volumeGradientOpacity->AddPoint(100, 1.0);

    vtkNew<vtkVolumeProperty> volumeProperty;
    volumeProperty->SetColor(volumeColor);
    volumeProperty->SetScalarOpacity(volumeScalarOpacity);
    volumeProperty->SetGradientOpacity(volumeGradientOpacity);
    volumeProperty->SetInterpolationTypeToLinear();
    volumeProperty->ShadeOn();
    volumeProperty->SetAmbient(0.4);
    volumeProperty->SetDiffuse(0.6);
    volumeProperty->SetSpecular(0.2);

    // The vtkVolume is a vtkProp3D (like a vtkActor) and controls the position
    // and orientation of the volume in world coordinates.
    vtkNew<vtkVolume> volume;
    volume->SetMapper(volumeMapper);
    volume->SetProperty(volumeProperty);

    //Set the renderer, renderwindow and renderwindow interactor
    vtkNew<vtkRenderer> render4;
    vtkNew<vtkGenericOpenGLRenderWindow> renderwindow4;
    viewerwidget4->setRenderWindow(renderwindow4); //Add to viewerwidget4
    renderwindow4->AddRenderer(render4);

    vtkNew<vtkRenderWindowInteractor> renderwindowinteractor4;
    renderwindowinteractor4->SetRenderWindow(renderwindow4);

    // Add the volume to the renderer
    render4->AddViewProp(volume);

    // Set up an initial view of the volume
    vtkCamera* camera4 = render4->GetActiveCamera();
    double* c = volume->GetCenter();
    camera4->SetViewUp(0, 0, -1);
    camera4->SetPosition(c[0], c[1] - 400, c[2]);
    camera4->SetFocalPoint(c[0], c[1], c[2]);
    camera4->Azimuth(30.0);
    camera4->Elevation(30.0);
    camera4->Dolly(0.5);

    // Control the camera to do interactors
    vtkNew<vtkInteractorStyleTrackballCamera> myInteractorStyle4;
    renderwindowinteractor4->SetInteractorStyle(myInteractorStyle4);

    // Interact with the data
    // render->Render();
    renderwindow4->Render();
    //renderwindowinteractor2->Start();
    renderwindow4->SetInteractor(renderwindowinteractor4);
    viewerwidget4->update();
}
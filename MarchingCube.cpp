#include<MarchingCube.h>

void MainWindow::marchingcube()
{
    QObject;

    //Set the color style
    vtkNew<vtkNamedColors> colors;
    std::array<unsigned char, 4> skinColor{ {240, 184, 160, 255} };
    colors->SetColor("SkinColor", skinColor.data());
    std::array<unsigned char, 4> backColor{ {255, 229, 200, 255} };
    colors->SetColor("BackfaceColor", backColor.data());
    std::array<unsigned char, 4> bkg{ {51, 77, 102, 255} };
    colors->SetColor("BkgColor", bkg.data());

    //Read data
    vtkNew<vtkDICOMImageReader> dicomseriesreader3;
    QString path = lineedit->text();
    QByteArray ba = path.toLocal8Bit();
    const char* path_str = ba.data();
    dicomseriesreader3->SetDirectoryName(path_str);

    //Marching cube operator
    vtkNew<vtkMarchingCubes> skinExtractor;
    skinExtractor->SetInputConnection(dicomseriesreader3->GetOutputPort());
    //skinExtractor->SetValue(0, 500);
    int num = spinbox->value();
    skinExtractor->SetValue(0, num);

    vtkNew<vtkPolyDataMapper> skinMapper;
    skinMapper->SetInputConnection(skinExtractor->GetOutputPort());
    skinMapper->ScalarVisibilityOff();

    vtkNew<vtkActor> skin;
    skin->SetMapper(skinMapper);
    skin->GetProperty()->SetDiffuseColor(
    colors->GetColor3d("SkinColor").GetData());

    vtkNew<vtkProperty> backProp;
    backProp->SetDiffuseColor(colors->GetColor3d("BackfaceColor").GetData());
    skin->SetBackfaceProperty(backProp);

    // An outline provides context around the data
    vtkNew<vtkOutlineFilter> outlineData;
    outlineData->SetInputConnection(dicomseriesreader3->GetOutputPort());

    vtkNew<vtkPolyDataMapper> mapOutline;
    mapOutline->SetInputConnection(outlineData->GetOutputPort());

    vtkNew<vtkActor> outline;
    outline->SetMapper(mapOutline);
    outline->GetProperty()->SetColor(colors->GetColor3d("Black").GetData());

    //Set the renderer, renderwindow and renderwindow interactor
    vtkNew<vtkRenderer> render5;
    vtkNew<vtkGenericOpenGLRenderWindow> renderwindow5;
    viewerwidget4->setRenderWindow(renderwindow5); //viewerwidget4
    renderwindow5->AddRenderer(render5);

    vtkNew<vtkRenderWindowInteractor> renderwindowinteractor5;
    renderwindowinteractor5->SetRenderWindow(renderwindow5);

    // An initial view of the data
    vtkNew<vtkCamera> camera5;
    camera5->SetViewUp(0, 0, -1);
    camera5->SetPosition(0, -1, 0);
    camera5->SetFocalPoint(0, 0, 0);
    camera5->ComputeViewPlaneNormal();
    camera5->Azimuth(30.0);
    camera5->Elevation(30.0);

    // Add Actors to the renderer
    render5->AddActor(outline);
    render5->AddActor(skin);
    render5->SetActiveCamera(camera5);
    render5->ResetCamera();
    camera5->Dolly(0.8); //moves the camera enlarging the image
    
    render5->ResetCameraClippingRange();

    // Control the camera to do interactors
    vtkNew<vtkInteractorStyleTrackballCamera> myInteractorStyle5;
    renderwindowinteractor5->SetInteractorStyle(myInteractorStyle5);

    // Initialize the event loop and then start it.
    renderwindow5->Render();
    renderwindowinteractor5->Initialize();
    renderwindow5->SetInteractor(renderwindowinteractor5);
    viewerwidget4->update();
}
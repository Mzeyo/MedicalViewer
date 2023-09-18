#include "OpenDICOMSeries.h"

void MainWindow::opendicomseries() 
{
    QObject;

    // Find the image directory
    QString folder = QFileDialog::getExistingDirectory();
    // Show path in the linebox
    QFileInfo OpenFileInfo;
    OpenFileInfo = QFileInfo(folder);
    QString OpenFilePath = OpenFileInfo.filePath();
    lineedit->setText(OpenFilePath);
    // Support path in Chinese
    QByteArray ba = folder.toLocal8Bit();
    const char* folder_str = ba.data();

    // Read the dicom series
    dicomseriesreader = vtkSmartPointer<vtkDICOMImageReader>::New();
    dicomseriesreader->SetDirectoryName(folder_str);
    dicomseriesreader->Update();

    // View the dicom series
    imageviewer = vtkSmartPointer<vtkImageViewer2>::New();
    imageviewer->SetInputConnection(dicomseriesreader->GetOutputPort());

    // Show the text information
    vtkSmartPointer<vtkTextProperty> sliceTextProp = vtkSmartPointer<vtkTextProperty>::New();
    sliceTextProp->SetFontFamilyToCourier();
    sliceTextProp->SetFontSize(15);
    sliceTextProp->SetVerticalJustificationToBottom();
    sliceTextProp->SetJustificationToLeft();

    vtkSmartPointer<vtkTextMapper> sliceTextMapper = vtkSmartPointer<vtkTextMapper>::New();
    std::string msg = StatusMessage::Format(imageviewer->GetSliceMin(), imageviewer->GetSliceMax());
    sliceTextMapper->SetInput(msg.c_str());
    sliceTextMapper->SetTextProperty(sliceTextProp);

    vtkSmartPointer<vtkActor2D> sliceTextActor = vtkSmartPointer<vtkActor2D>::New();
    sliceTextActor->SetMapper(sliceTextMapper);
    sliceTextActor->SetPosition(15, 10);

    // Show the instruction for operation
    vtkSmartPointer<vtkTextProperty> usageTextProp = vtkSmartPointer<vtkTextProperty>::New();
    usageTextProp->SetFontFamilyToCourier();
    usageTextProp->SetFontSize(20);
    usageTextProp->SetVerticalJustificationToTop();
    usageTextProp->SetJustificationToLeft();

    vtkSmartPointer<vtkTextMapper> usageTextMapper = vtkSmartPointer<vtkTextMapper>::New();
    usageTextMapper->SetInput("- Slice with mouse wheel\n  or Up/Down-Key\n- Zoom with pressed right\n  mouse button while dragging");
    usageTextMapper->SetTextProperty(usageTextProp);

    vtkSmartPointer<vtkActor2D> usageTextActor = vtkSmartPointer<vtkActor2D>::New();
    usageTextActor->SetMapper(usageTextMapper);
    usageTextActor->GetPositionCoordinate()->SetCoordinateSystemToNormalizedDisplay();
    usageTextActor->GetPositionCoordinate()->SetValue(0.05, 0.95);

    // The interactor action and connection
    vtkSmartPointer<vtkRenderWindowInteractor> renderwindowinteractor = vtkSmartPointer<vtkRenderWindowInteractor>::New();
    vtkSmartPointer<myVtkInteractorStyleImage> myInteractorStyle = vtkSmartPointer<myVtkInteractorStyleImage>::New();
    myInteractorStyle->SetStatusMapper(sliceTextMapper);

    // Load the image data，interactor action and text information into the VTK rendering window
    vtkSmartPointer<vtkGenericOpenGLRenderWindow> renderwindowXY= vtkSmartPointer<vtkGenericOpenGLRenderWindow>::New();
    imageviewer->SetRenderWindow(renderwindowXY);
    imageviewer->SetupInteractor(renderwindowXY->GetInteractor());
    viewerwidget1->setRenderWindow(imageviewer->GetRenderWindow());

    imageviewer->GetRenderer()->AddActor2D(sliceTextActor);
    imageviewer->GetRenderer()->AddActor2D(usageTextActor);

    imageviewer->SetupInteractor(renderwindowinteractor);
    myInteractorStyle->SetImageViewer(imageviewer);
    renderwindowinteractor->SetInteractorStyle(myInteractorStyle);

    imageviewer->Render();
    //imageviewer->GetRenderer()->ResetCamera();
    //renderwindowinteractor->Initialize();
    viewerwidget1->update();
}

void MainWindow::opendicomseriesYZ()
{
    QObject;

    //Read data
    vtkNew<vtkDICOMImageReader> dicomseriesreader;
    QString path = lineedit->text();
    QByteArray ba = path.toLocal8Bit();
    const char* path_str = ba.data();
    dicomseriesreader->SetDirectoryName(path_str);

    // Read the dicom series
    dicomseriesreader->SetDirectoryName(path_str);
    dicomseriesreader->Update();

    // View the dicom series
    imageviewerYZ = vtkSmartPointer<vtkImageViewer2>::New();
    imageviewerYZ->SetInputConnection(dicomseriesreader->GetOutputPort());
    imageviewerYZ->SetSliceOrientationToYZ();

    // Show the text information
    vtkSmartPointer<vtkTextProperty> sliceTextProp = vtkSmartPointer<vtkTextProperty>::New();
    sliceTextProp->SetFontFamilyToCourier();
    sliceTextProp->SetFontSize(15);
    sliceTextProp->SetVerticalJustificationToBottom();
    sliceTextProp->SetJustificationToLeft();

    vtkSmartPointer<vtkTextMapper> sliceTextMapper = vtkSmartPointer<vtkTextMapper>::New();
    std::string msg = StatusMessage::Format(imageviewerYZ->GetSliceMin(), imageviewerYZ->GetSliceMax());
    sliceTextMapper->SetInput(msg.c_str());
    sliceTextMapper->SetTextProperty(sliceTextProp);

    vtkSmartPointer<vtkActor2D> sliceTextActor = vtkSmartPointer<vtkActor2D>::New();
    sliceTextActor->SetMapper(sliceTextMapper);
    sliceTextActor->SetPosition(15, 10);

    // Show the instruction for operation
    vtkSmartPointer<vtkTextProperty> usageTextProp = vtkSmartPointer<vtkTextProperty>::New();
    usageTextProp->SetFontFamilyToCourier();
    usageTextProp->SetFontSize(20);
    usageTextProp->SetVerticalJustificationToTop();
    usageTextProp->SetJustificationToLeft();

    vtkSmartPointer<vtkTextMapper> usageTextMapper = vtkSmartPointer<vtkTextMapper>::New();
    usageTextMapper->SetInput("- Slice Direction: YZ");
    usageTextMapper->SetTextProperty(usageTextProp);

    vtkSmartPointer<vtkActor2D> usageTextActor = vtkSmartPointer<vtkActor2D>::New();
    usageTextActor->SetMapper(usageTextMapper);
    usageTextActor->GetPositionCoordinate()->SetCoordinateSystemToNormalizedDisplay();
    usageTextActor->GetPositionCoordinate()->SetValue(0.05, 0.95);

    // The interactor action and connection
    vtkSmartPointer<vtkRenderWindowInteractor> renderwindowinteractor = vtkSmartPointer<vtkRenderWindowInteractor>::New();
    vtkSmartPointer<myVtkInteractorStyleImage> myInteractorStyle = vtkSmartPointer<myVtkInteractorStyleImage>::New();
    myInteractorStyle->SetStatusMapper(sliceTextMapper);

    // Load the image data，interactor action and text information into the VTK rendering window
    vtkSmartPointer<vtkGenericOpenGLRenderWindow> renderwindowYZ = vtkSmartPointer<vtkGenericOpenGLRenderWindow>::New();
    imageviewerYZ->SetRenderWindow(renderwindowYZ);
    imageviewerYZ->SetupInteractor(renderwindowYZ->GetInteractor());
    viewerwidget2->setRenderWindow(imageviewerYZ->GetRenderWindow());

    imageviewerYZ->GetRenderer()->AddActor2D(sliceTextActor);
    imageviewerYZ->GetRenderer()->AddActor2D(usageTextActor);

    imageviewerYZ->SetupInteractor(renderwindowinteractor);
    myInteractorStyle->SetImageViewer(imageviewerYZ);
    renderwindowinteractor->SetInteractorStyle(myInteractorStyle);

    imageviewerYZ->Render();
    //imageviewerYZ->GetRenderer()->ResetCamera();
    //renderwindowinteractor->Initialize();

    viewerwidget2->update();
}

void MainWindow::opendicomseriesXZ()
{
    QObject;

    //Read data
    vtkNew<vtkDICOMImageReader> dicomseriesreader;
    QString path = lineedit->text();
    QByteArray ba = path.toLocal8Bit();
    const char* path_str = ba.data();
    dicomseriesreader->SetDirectoryName(path_str);

    // Read the dicom series
    dicomseriesreader->SetDirectoryName(path_str);
    dicomseriesreader->Update();

    // View the dicom series
    imageviewerXZ = vtkSmartPointer<vtkImageViewer2>::New();
    imageviewerXZ->SetInputConnection(dicomseriesreader->GetOutputPort());
    imageviewerXZ->SetSliceOrientationToXZ();

    // Show the text information
    vtkSmartPointer<vtkTextProperty> sliceTextProp = vtkSmartPointer<vtkTextProperty>::New();
    sliceTextProp->SetFontFamilyToCourier();
    sliceTextProp->SetFontSize(15);
    sliceTextProp->SetVerticalJustificationToBottom();
    sliceTextProp->SetJustificationToLeft();

    vtkSmartPointer<vtkTextMapper> sliceTextMapper = vtkSmartPointer<vtkTextMapper>::New();
    std::string msg = StatusMessage::Format(imageviewerXZ->GetSliceMin(), imageviewerXZ->GetSliceMax());
    sliceTextMapper->SetInput(msg.c_str());
    sliceTextMapper->SetTextProperty(sliceTextProp);

    vtkSmartPointer<vtkActor2D> sliceTextActor = vtkSmartPointer<vtkActor2D>::New();
    sliceTextActor->SetMapper(sliceTextMapper);
    sliceTextActor->SetPosition(15, 10);

    // Show the instruction for operation
    vtkSmartPointer<vtkTextProperty> usageTextProp = vtkSmartPointer<vtkTextProperty>::New();
    usageTextProp->SetFontFamilyToCourier();
    usageTextProp->SetFontSize(20);
    usageTextProp->SetVerticalJustificationToTop();
    usageTextProp->SetJustificationToLeft();

    vtkSmartPointer<vtkTextMapper> usageTextMapper = vtkSmartPointer<vtkTextMapper>::New();
    usageTextMapper->SetInput("- Slice Direction: XZ");
    usageTextMapper->SetTextProperty(usageTextProp);

    vtkSmartPointer<vtkActor2D> usageTextActor = vtkSmartPointer<vtkActor2D>::New();
    usageTextActor->SetMapper(usageTextMapper);
    usageTextActor->GetPositionCoordinate()->SetCoordinateSystemToNormalizedDisplay();
    usageTextActor->GetPositionCoordinate()->SetValue(0.05, 0.95);

    // The interactor action and connection
    vtkSmartPointer<vtkRenderWindowInteractor> renderwindowinteractor = vtkSmartPointer<vtkRenderWindowInteractor>::New();
    vtkSmartPointer<myVtkInteractorStyleImage> myInteractorStyle = vtkSmartPointer<myVtkInteractorStyleImage>::New();
    myInteractorStyle->SetStatusMapper(sliceTextMapper);

    // Load the image data，interactor action and text information into the VTK rendering window
    vtkSmartPointer<vtkGenericOpenGLRenderWindow> renderwindowXZ = vtkSmartPointer<vtkGenericOpenGLRenderWindow>::New();
    imageviewerXZ->SetRenderWindow(renderwindowXZ);
    imageviewerXZ->SetupInteractor(renderwindowXZ->GetInteractor());
    viewerwidget3->setRenderWindow(imageviewerXZ->GetRenderWindow());

    imageviewerXZ->GetRenderer()->AddActor2D(sliceTextActor);
    imageviewerXZ->GetRenderer()->AddActor2D(usageTextActor);

    imageviewerXZ->SetupInteractor(renderwindowinteractor);
    myInteractorStyle->SetImageViewer(imageviewerXZ);
    renderwindowinteractor->SetInteractorStyle(myInteractorStyle);

    imageviewerXZ->Render();
    //imageviewerXZ->GetRenderer()->ResetCamera();
    //renderwindowinteractor->Initialize();

    viewerwidget3->update();
}



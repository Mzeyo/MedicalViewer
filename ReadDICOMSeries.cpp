#include "mainwindow.h"
#include "ReadDICOMSeries.h"

int MainWindow::ReadDICOMSeries_main()
{
    QObject;
    // Find the image directory
    QString folder = QFileDialog::getExistingDirectory(); 
    // Show path in the linebox
    QFileInfo OpenFileInfo;
    OpenFileInfo = QFileInfo(folder);
    QString OpenFilePath = OpenFileInfo.filePath();
    ui.lineEdit->setText(OpenFilePath);
    // Support path in Chinese
    QByteArray ba = folder.toLocal8Bit();
    const char* folder_str = ba.data();

    // Read the dicom series
    dicomseriesReader = vtkSmartPointer<vtkDICOMImageReader>::New();
    dicomseriesReader->SetDirectoryName(folder_str);
    dicomseriesReader->Update();

    // View the dicom series
    imageViewer = vtkSmartPointer<vtkImageViewer2>::New();
    imageViewer->SetInputConnection(dicomseriesReader->GetOutputPort());

    // Show the text information around the image
    vtkSmartPointer<vtkTextProperty> sliceTextProp = vtkSmartPointer<vtkTextProperty>::New();
    sliceTextProp->SetFontFamilyToCourier();
    sliceTextProp->SetFontSize(20);
    sliceTextProp->SetVerticalJustificationToBottom();
    sliceTextProp->SetJustificationToLeft();

    vtkSmartPointer<vtkTextMapper> sliceTextMapper = vtkSmartPointer<vtkTextMapper>::New();
    std::string msg = StatusMessage::Format(imageViewer->GetSliceMin(), imageViewer->GetSliceMax());
    sliceTextMapper->SetInput(msg.c_str());
    sliceTextMapper->SetTextProperty(sliceTextProp);

    vtkSmartPointer<vtkActor2D> sliceTextActor = vtkSmartPointer<vtkActor2D>::New();
    sliceTextActor->SetMapper(sliceTextMapper);
    sliceTextActor->SetPosition(15, 10);

    // Show the instruction for operation
    vtkSmartPointer<vtkTextProperty> usageTextProp = vtkSmartPointer<vtkTextProperty>::New();
    usageTextProp->SetFontFamilyToCourier();
    usageTextProp->SetFontSize(14);
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
    vtkSmartPointer<vtkRenderWindowInteractor> renderWindowInteractor = vtkSmartPointer<vtkRenderWindowInteractor>::New();
    vtkSmartPointer<myVtkInteractorStyleImage> myInteractorStyle = vtkSmartPointer<myVtkInteractorStyleImage>::New();
    myInteractorStyle->SetStatusMapper(sliceTextMapper);
    
   // Load the image data，interactor action and text information into the VTK rendering window
    vtkSmartPointer<vtkGenericOpenGLRenderWindow> renderWindow = vtkSmartPointer<vtkGenericOpenGLRenderWindow>::New();
    imageViewer->SetRenderWindow(renderWindow);
    imageViewer->SetupInteractor(renderWindow->GetInteractor());
    ui.qvtkWidget->setRenderWindow(imageViewer->GetRenderWindow());

    imageViewer->GetRenderer()->AddActor2D(sliceTextActor);
    imageViewer->GetRenderer()->AddActor2D(usageTextActor);

    imageViewer->SetupInteractor(renderWindowInteractor);
    myInteractorStyle->SetImageViewer(imageViewer);
    renderWindowInteractor->SetInteractorStyle(myInteractorStyle);
    
    imageViewer->Render();
    imageViewer->GetRenderer()->ResetCamera();
    ui.qvtkWidget->update();

    return 0;
}
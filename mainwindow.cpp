#include "mainwindow.h"

MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);

    Renderer = vtkSmartPointer<vtkRenderer>::New();
    ImageData = vtkSmartPointer<vtkImageData>::New();
    ImageActor = vtkSmartPointer<vtkImageActor>::New();

    // Eliminate version warnings of VTK
    vtkOutputWindow::SetGlobalWarningDisplay(0);

    // Set the renderWindow for qvtkWidget
    ui.qvtkWidget->renderWindow()->AddRenderer(Renderer);

    // Connect the signals and slots
    connect(ui.pushButton, SIGNAL(clicked(bool)), this, SLOT(Readimage_main()));
    connect(ui.pushButton_2, SIGNAL(clicked(bool)), this, SLOT(ReadDICOMSeries_main()));
}

// Read images end with .dcm, .png, .jpg, .jpeg
void MainWindow::Readimage_main(void)
{
    // Find the image
    QString FileInstruction;
    FileInstruction = "Image Files(*.dcm *.png *.jpg *.jpeg);;All(*.*)";
    QDir FileDir;
    QString imagePath = QFileDialog::getOpenFileName(this, QString(tr("打开图像")), "", FileInstruction);
 
    if (imagePath.isEmpty() == true)
    {
        cout << "error" << endl;
        return;
    }
    // Show path in the linebox
    QFileInfo OpenFileInfo;
    OpenFileInfo = QFileInfo(imagePath);
    QString OpenFilePath = OpenFileInfo.filePath();
    ui.lineEdit->setText(OpenFilePath);
    // Support path in Chinese
    QByteArray ba = imagePath.toLocal8Bit();
    const char* imagePath_str = ba.data();

    // Define the corresponding image reader based on the file type
    if (imagePath.endsWith(".dcm"))
    {
        vtkSmartPointer<vtkDICOMImageReader> dicomReader = vtkSmartPointer<vtkDICOMImageReader>::New();
        dicomReader->SetFileName(imagePath_str);
  
        dicomReader->Update();
        ImageData = dicomReader->GetOutput();

    }
    else if (imagePath.endsWith(".png"))
    {
        vtkSmartPointer<vtkPNGReader> pngReader = vtkSmartPointer<vtkPNGReader>::New();
        pngReader->SetFileName(imagePath_str);
        pngReader->Update();
        ImageData = pngReader->GetOutput();
    }
    else if (imagePath.endsWith(".jpg") || imagePath.endsWith(".jpeg"))
    {
        vtkSmartPointer<vtkJPEGReader> jpegReader = vtkSmartPointer<vtkJPEGReader>::New();
        jpegReader->SetFileName(imagePath_str);
        jpegReader->Update();
        ImageData = jpegReader->GetOutput();
    }

    // Load the image data into the VTK rendering window
    ui.qvtkWidget->renderWindow()->AddRenderer(Renderer);
    ImageActor->SetInputData(ImageData);
    Renderer->AddActor(ImageActor);
    Renderer->ResetCamera();
    ui.qvtkWidget->renderWindow()->Render();
}


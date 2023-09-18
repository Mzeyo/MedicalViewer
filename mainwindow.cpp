#include "mainwindow.h"

MainWindow::MainWindow(QMainWindow* parent)
    : QMainWindow(parent)
{
    initwindow();
    initslots();
} 

MainWindow::~MainWindow()
{
}

void MainWindow::initwindow() {
    // Set the mainwindow
    this->setObjectName(QString::fromUtf8("MedicalDemo"));
    this->resize(1600, 1200);
    centralwidget = new QWidget(this);
    this->setCentralWidget(centralwidget);

    // Define the PushButton, LineEdit and SpinBox
    openbutton = new QPushButton("Open DICOM Series");
    marchingcubebutton = new QPushButton("Marching Cube Operation");
    volumebutton = new QPushButton("Volume Rendering");
    lineedit = new QLineEdit();

    label = new QLabel();
    label->setText("Set the contour value :");
    label->setAlignment(Qt::AlignRight | Qt::AlignVCenter);

    spinbox = new QSpinBox(this);
    //spinbox->setPrefix("Set the contour value :");
    spinbox->setRange(0, 1000); // Range
    spinbox->setSingleStep(50); // Step
    spinbox->setValue(80); // Origin

    //Layout
    mainlayout = new QVBoxLayout(centralwidget);

    layout1 = new QHBoxLayout();
    layout1->addWidget(openbutton);
    layout1->addWidget(volumebutton);
    layout1->addWidget(marchingcubebutton);
    layout1->addWidget(label);
    layout1->addWidget(spinbox);
    layout1->setStretch(0, 2);
    layout1->setStretch(1, 2);
    layout1->setStretch(2, 2);

    layout2 = new QGridLayout();
    layout2->addWidget(lineedit);

    layout3 = new QHBoxLayout();
    viewerwidget1 = new QVTKOpenGLNativeWidget(this);
    layout3->addWidget(viewerwidget1);
    viewerwidget2 = new QVTKOpenGLNativeWidget(this);
    layout3->addWidget(viewerwidget2);
    
    layout4 = new QHBoxLayout();
    viewerwidget3 = new QVTKOpenGLNativeWidget(this);
    layout4->addWidget(viewerwidget3);
    viewerwidget4 = new QVTKOpenGLNativeWidget(this);
    layout4->addWidget(viewerwidget4);

    mainlayout->addLayout(layout1);
    mainlayout->addLayout(layout2);
    mainlayout->addLayout(layout3);
    mainlayout->addLayout(layout4);
}

void MainWindow::initslots() 
{
    connect(openbutton, SIGNAL(clicked(bool)), this, SLOT(opendicomseries()), Qt::UniqueConnection);
    connect(openbutton, SIGNAL(clicked(bool)), this, SLOT(opendicomseriesYZ()), Qt::UniqueConnection);
    connect(openbutton, SIGNAL(clicked(bool)), this, SLOT(opendicomseriesXZ()), Qt::UniqueConnection);
    connect(marchingcubebutton, SIGNAL(clicked(bool)), this, SLOT(marchingcube()));
    connect(volumebutton, SIGNAL(clicked(bool)), this, SLOT(volumerendering()));
}


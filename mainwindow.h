#pragma once

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QApplication>
#include <QMainWindow>
#include <QLineEdit>
#include <QPushButton>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QLabel>
#include <QFileDialog>
#include <QSpinBox>
#include <QFormlayout.h>

#include <QVTKOpenGLNativeWidget.h>

#include <MarchingCube.h>
#include <OpenDICOMSeries.h>
#include <VolumeRendering.h>
#include "vtkAutoInit.h"

#include <vtkOutputWindow.h>

VTK_MODULE_INIT(vtkRenderingOpenGL2);
VTK_MODULE_INIT(vtkInteractionStyle);
VTK_MODULE_INIT(vtkRenderingFreeType);

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QMainWindow* parent = nullptr);
    ~MainWindow();

    void initwindow();
    
private:
    QWidget *centralwidget; 
    QVTKOpenGLNativeWidget* viewerwidget1;
    QVTKOpenGLNativeWidget* viewerwidget2;
    QVTKOpenGLNativeWidget* viewerwidget3;
    QVTKOpenGLNativeWidget* viewerwidget4;
    QVBoxLayout *mainlayout;
    QHBoxLayout *layout1;
    QGridLayout* layout2;
    QHBoxLayout* layout3;
    QHBoxLayout* layout4;
    QFormLayout* formlayout;
    QLineEdit *lineedit;
    QPushButton *openbutton;
    QPushButton * marchingcubebutton;
    QPushButton *volumebutton;
    QLabel *label;
    QString *OpenFilePath;
    QSpinBox* spinbox;

    void initslots();

private slots:
    void opendicomseries();
    void opendicomseriesYZ();
    void opendicomseriesXZ();

    void marchingcube();

    void volumerendering();

private:
    vtkSmartPointer<vtkDICOMImageReader> dicomseriesreader;
    vtkSmartPointer<vtkImageViewer2> imageviewer; 
    vtkSmartPointer<vtkImageViewer2> imageviewerYZ;
    vtkSmartPointer<vtkImageViewer2> imageviewerXZ;
};
#endif // MAINWINDOW_H

#pragma once 

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#ifdef  _IM_PUBLIC_FUNCTION_
#  define CPPSQLITE_API  __declspec(dllexport)
#else
#  define CPPSQLITE_API  __declspec(dllimport)
#endif

// Qt
#include <QMainWindow>
#include "ui_mainwindow.h"
#include <QFileDialog>
#include <QDir>
#include <qstring.h>
#include <qlineedit.h>
#include <QpushButton>
// VTK
#include <vtkRenderer.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkImageViewer2.h>
#include <vtkImageData.h>
#include <vtkImageActor.h>
#include <vtkDICOMImageReader.h>
#include <vtkPNGReader.h>
#include <vtkJPEGReader.h>
#include <QVTKOpenGLNativeWidget.h>
#include <vtkGenericOpenGLRenderWindow.h>
#include <vtkSmartPointer.h>
#include <vtkInteractorStyleImage.h>
#include <vtkEventQtSlotConnect.h>
#include "vtkCommand.h"
#include <vtkOutputWindow.h>
#include "vtkAutoInit.h"
#include <vtkActor.h>
#include <vtkActor2D.h>
#include <vtkTextMapper.h>
#include <vtkTextProperty.h>
#include <vtkNew.h>
#include <vtkObjectFactory.h>
#include<iostream>
#include<string.h>

class MainWindow : public QMainWindow
{
    Q_OBJECT
   
public:
    MainWindow(QWidget* parent = Q_NULLPTR);

private:
    Ui::MainWindow ui;

private slots:
    void Readimage_main(void);
    int ReadDICOMSeries_main();

private:
    vtkSmartPointer<vtkDICOMImageReader> dicomseriesReader;
    vtkSmartPointer<vtkImageViewer2> imageViewer;
    vtkSmartPointer<vtkRenderer> Renderer;
    vtkSmartPointer<vtkImageData> ImageData;
    vtkSmartPointer<vtkImageActor> ImageActor;
};
#endif // MAINWINDOW_H
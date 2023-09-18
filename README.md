# MedicalViewer

## Introduction
This is the source code for reading and viewing medical images in different types mainly based on VTK & QT, completing MarchingCube and Volume rendering operation simultaneously, which is available for modification by commiting.

## Features
- Select the type of medical images by pushing the Open File button, the folder path of which can be displayed in the lineedit box;
- Single images can be displayed directly, and sliding the mouse wheel can achieve the size scaling;
- The display of dicom series needs to be achieved within a few seconds after selecting the image folder;
- What can be seen is the approach for the image viewing operation in the upper left corner of the image widget, and the number of the current slice and the total slices of the whole folder being displayed in the lower left corner;
- Follow the approach above to realize the irregularly changing the intensity, size, and slice scrolling of the medical image;
- The top right and bottom left corners of the interface display the other two views of the image, which allows the irregular changes of the intensity, size, and slice scrolling of the medical image;
- After reading a volume dataset, pushing the Volume Rendering button means displaying the three-dimensional visualization;
- After reading a volume dataset, pushing the MarchingCube Operation button means extracting an isosurface that represents the skin and displaying it on the bottom corner of the interface. The isosurface, or contour value can be changed in the range of 0 to 500, which is known to correspond to the skin of the patient.
  
## Requirements
During the compilation process, you need to pay special attention to the ***version requirements*** of each software as follows: 
- VTK 9.2.4 
- Qt 5.15.2 
- Microsoft Visual Studio 2019 or newer

## Example Results

[Click to view the example](https://github.com/Mzeyo/MedicalViewer/blob/main/Example.jpg)

#include <vtkVersion.h>
#include <vtkSmartPointer.h>
#include <vtkStructuredGrid.h>
#include <vtkXMLStructuredGridWriter.h>
#include <vtkMath.h>
#include <vtkPolyData.h>
#include <vtkPointData.h>
#include <vtkPolyDataMapper.h>
#include <vtkProperty.h>
#include <vtkActor.h>
#include <vtkRenderWindow.h>
#include <vtkRenderer.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkStructuredGridGeometryFilter.h>
#include <vtkVertexGlyphFilter.h>


#include <vtkPoints.h>
 
#include <vtkLookupTable.h>

#include "structure.h"

void visualizePoints(Structure& structure)
{
  // Create a grid
  vtkSmartPointer<vtkStructuredGrid> structuredGrid = 
    vtkSmartPointer<vtkStructuredGrid>::New();

 
  vtkSmartPointer<vtkPolyData> pointsPolydata =
    vtkSmartPointer<vtkPolyData>::New(); 

  vtkSmartPointer<vtkPoints> points = 
    vtkSmartPointer<vtkPoints>::New();
 
  double dimx = 10;
  double dimy = 10;
  double dimz = 10;

  for(unsigned int i = 0; i < dimx; i++)
    {
    for(unsigned int j = 0; j < dimy; j++)
      {
      for(unsigned int k = 0; k < dimz; k++)
        {
		// first the corners
		for (const auto & elem : structure.getVectors().first){
			points->InsertNextPoint(elem[0]+i, elem[1]+j, elem[2]+k);
		}

		// then the faces / body
		for (const auto & elem : structure.getVectors().second){
			points->InsertNextPoint(elem[0]+i, elem[1]+j, elem[2]+k);
		}
        }
      }
    }

  pointsPolydata->SetPoints(points);
 
  vtkSmartPointer<vtkVertexGlyphFilter> vertexFilter =
    vtkSmartPointer<vtkVertexGlyphFilter>::New();
#if VTK_MAJOR_VERSION <= 5
  vertexFilter->SetInputConnection(pointsPolydata->GetProducerPort());
#else
  vertexFilter->SetInputData(pointsPolydata);
#endif
  vertexFilter->Update();
 
  vtkSmartPointer<vtkPolyData> polydata =
    vtkSmartPointer<vtkPolyData>::New();
  polydata->ShallowCopy(vertexFilter->GetOutput());

  // Setup colors
  unsigned char red[3] = {255, 0, 0};
  unsigned char green[3] = {0, 255, 0};
  unsigned char blue[3] = {0, 0, 255};
 
  vtkSmartPointer<vtkUnsignedCharArray> colors =
    vtkSmartPointer<vtkUnsignedCharArray>::New();
  colors->SetNumberOfComponents(3);
  colors->SetName ("Colors");
  colors->InsertNextTupleValue(red);
  colors->InsertNextTupleValue(green);
  colors->InsertNextTupleValue(blue);
 
  polydata->GetPointData()->SetScalars(colors);


  // Specify the dimensions of the grid
  structuredGrid->SetDimensions(dimx, dimy, dimz);
  structuredGrid->SetPoints(points);
 
  std::cout << "There are " << structuredGrid->GetNumberOfPoints() << " points." << std::endl; 
 
  vtkSmartPointer<vtkStructuredGridGeometryFilter> geometryFilter = 
    vtkSmartPointer<vtkStructuredGridGeometryFilter>::New();
#if VTK_MAJOR_VERSION <= 5
  geometryFilter->SetInputConnection(structuredGrid->GetProducerPort());
#else
  geometryFilter->SetInputData(structuredGrid);
#endif
  geometryFilter->Update();
 



  // Create a mapper and actor
  vtkSmartPointer<vtkPolyDataMapper> mapper = 
    vtkSmartPointer<vtkPolyDataMapper>::New();
#if VTK_MAJOR_VERSION <= 5
  mapper->SetInputConnection(polydata->GetProducerPort());
#else
  mapper->SetInputData(polydata);
#endif

#if VTK_MAJOR_VERSION <= 5
  mapper->SetInputConnection(geometryFilter->GetProducerPort());
#else
  mapper->SetInputData(polydata);
#endif

  vtkSmartPointer<vtkActor> actor = 
    vtkSmartPointer<vtkActor>::New();
  actor->SetMapper(mapper);
  actor->GetProperty()->SetPointSize(7);
 
  // Visualize
  vtkSmartPointer<vtkRenderer> renderer = 
    vtkSmartPointer<vtkRenderer>::New();
  vtkSmartPointer<vtkRenderWindow> renderWindow = 
    vtkSmartPointer<vtkRenderWindow>::New();
  renderWindow->AddRenderer(renderer);
  vtkSmartPointer<vtkRenderWindowInteractor> renderWindowInteractor = 
    vtkSmartPointer<vtkRenderWindowInteractor>::New();
  renderWindowInteractor->SetRenderWindow(renderWindow);
 
  renderer->AddActor(actor);
  renderer->SetBackground(.2, .3, .4);
 
  renderWindow->Render();
  renderWindowInteractor->Start();

}

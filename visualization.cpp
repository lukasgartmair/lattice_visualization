#include <vtkVersion.h>
#include <vtkSmartPointer.h>
#include <vtkStructuredGrid.h>
#include <vtkXMLStructuredGridWriter.h>
#include <vtkMath.h>
#include <vtkPolyDataMapper.h>
#include <vtkProperty.h>
#include <vtkActor.h>
#include <vtkRenderWindow.h>
#include <vtkRenderer.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkStructuredGridGeometryFilter.h>

#include "structure.h"

void visualizePoints(Structure& structure)
{
  // Create a grid
  vtkSmartPointer<vtkStructuredGrid> structuredGrid = 
    vtkSmartPointer<vtkStructuredGrid>::New();
 
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
  mapper->SetInputConnection(geometryFilter->GetOutputPort());
  vtkSmartPointer<vtkActor> actor = 
    vtkSmartPointer<vtkActor>::New();
  actor->SetMapper(mapper);
  actor->GetProperty()->SetPointSize(3);
 
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

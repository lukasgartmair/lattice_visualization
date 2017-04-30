
cmake_minimum_required(VERSION 3.5)

PROJECT(lattice_viz)

set(INCLUDE_DIR /home/lukas/lattice_viz)
include_directories (${INCLUDE_DIR})     # make sure your .h all inside.


find_package(VTK REQUIRED)
include(${VTK_USE_FILE})

set (CMAKE_CXX_STANDARD 11)

add_library (structure structure.cpp structure.h)
add_library (visualization visualization.cpp visualization.h)

add_executable(lattice_viz MACOSX_BUNDLE lattice_viz.cpp)

if(VTK_LIBRARIES)
  target_link_libraries(lattice_viz structure visualization ${VTK_LIBRARIES})
else()
  target_link_libraries(lattice_viz structure visualization vtkHybrid vtkWidgets)
endif()

#include "structure.h"
#include "visualization.h"
#include <iostream>

int main(){

Structure s1("fcc");

std::cout << s1.getLatticeType() << std::endl;

const double lattice_constant = 1.0;
s1.initializeVectors(lattice_constant);

s1.printVectors();

visualizePoints(s1);

return 0;
}

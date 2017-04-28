#include "structure.h"
#include "atom.h"
#include "visualization.h"
#include <iostream>

int main(){

Structure s1("fcc");

std::cout << s1.getLatticeType() << std::endl;

s1.initializeBaseVectors();

s1.getBaseVectors();

return 0;
}

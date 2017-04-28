#include "structure.h"
#include <iostream>
#include <algorithm>


const unsigned int dimension {3};


Structure::Structure() : lattice_type(""), base_vecs(dimension, std::vector<double>(dimension)) {}

Structure::Structure(const std::string lt) : lattice_type(lt), base_vecs(dimension, std::vector<double>(dimension)) {std::cout << "structure " << lattice_type << " created\n";}  

Structure::Structure(Structure& s) : lattice_type(s.lattice_type) {}

Structure::~Structure(){std::cout << "structure " << lattice_type << " deleted\n";}

std::string Structure::getLatticeType(){
	return lattice_type;
}

void Structure::initializeBaseVectors(const double& lattice_constant = 1.0){
	
	if ("cubic" == lattice_type){

		base_vecs[0] = {1.0,0.0,0.0};
		base_vecs[1] = {0.0,1.0,0.0};
		base_vecs[2] = {0.0,0.0,1.0};
	}

	else if ("fcc" == lattice_type){

		base_vecs[0] = {0.0,0.5,0.5};
		base_vecs[1] = {0.5,0.0,0.5};
		base_vecs[2] = {0.5,0.5,0.0};
	}

	else if ("bcc" == lattice_type){

		base_vecs[0] = {-0.5,0.5,0.5};
		base_vecs[1] = {0.5,-0.5,0.5};
		base_vecs[2] = {0.5,0.5,-0.5};
	}

	// multiplication of all base vec values with the lattice constant
	for(unsigned int ui=0;ui<dimension;++ui){
		std::transform(base_vecs[ui].begin(), base_vecs[ui].end(), base_vecs[ui].begin(),
			       std::bind1st(std::multiplies<double>(),lattice_constant));
	}
}

void Structure::getBaseVectors(){

	for(unsigned int ui=0;ui<dimension;++ui){
		for(unsigned int uj=0;uj<dimension;++uj){
			std::cout << base_vecs[ui][uj] << std::endl;	
		}
	}

}



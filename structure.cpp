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

void Structure::initializeVectors(const double& lattice_constant = 1.0){

	if ("cubic" == lattice_type){

		base_vecs[0] = {1.0,0.0,0.0};
		base_vecs[1] = {0.0,1.0,0.0};
		base_vecs[2] = {0.0,0.0,1.0};
	}

	if ("fcc" == lattice_type){

		base_vecs[0] = {0.0,0.5,0.5};
		base_vecs[1] = {0.5,0.0,0.5};
		base_vecs[2] = {0.5,0.5,0.0};
	}

	if ("bcc" == lattice_type){

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

nested_double_vec Structure::getVectors(){

	return base_vecs;
}

void Structure::printVectors(){

	// first the corners
	for (const auto & elem : getVectors()){
		std::cout << elem[0] << elem[1] << elem[2] << " position\n";
	}
}




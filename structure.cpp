#include "structure.h"
#include <iostream>
#include <algorithm>


const unsigned int dimension {3};


Structure::Structure() : lattice_type(""), corner_vecs(dimension, std::vector<double>(dimension)), base_vecs(dimension, std::vector<double>(dimension)) {}

Structure::Structure(const std::string lt) : lattice_type(lt), corner_vecs(dimension, std::vector<double>(dimension)), base_vecs(dimension, std::vector<double>(dimension)) {std::cout << "structure " << lattice_type << " created\n";}  

Structure::Structure(Structure& s) : lattice_type(s.lattice_type) {}

Structure::~Structure(){std::cout << "structure " << lattice_type << " deleted\n";}

std::string Structure::getLatticeType(){
	return lattice_type;
}

void Structure::initializeVectors(const double& lattice_constant = 1.0){
	
	corner_vecs[0] = {1.0,0.0,0.0};
	corner_vecs[1] = {0.0,1.0,0.0};
	corner_vecs[2] = {0.0,0.0,1.0};

	// multiplication of all base vec values with the lattice constant
	for(unsigned int ui=0;ui<dimension;++ui){
		std::transform(corner_vecs[ui].begin(), corner_vecs[ui].end(), corner_vecs[ui].begin(),
			       std::bind1st(std::multiplies<double>(),lattice_constant));
	}

	if ("cubic" == lattice_type){

		base_vecs[0] = {0.0,0.0,0.0};
		base_vecs[1] = {0.0,0.0,0.0};
		base_vecs[2] = {0.0,0.0,0.0};
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

std::pair <nested_double_vec,nested_double_vec> Structure::getVectors(){
	
	std::pair <nested_double_vec,nested_double_vec> vectors;
  	vectors = std::make_pair (corner_vecs, base_vecs);
	return vectors;
}

void Structure::printVectors(){

	// first the corners
	for (const auto & elem : getVectors().first){
		std::cout << elem[0] << elem[1] << elem[2] << " position\n";
	}

	// then the faces / body
	// first the corners
	for (const auto & elem : getVectors().second){
		std::cout << elem[0] << elem[1] << elem[2] << " position\n";
	}

}




#ifndef STRUCTURE_H
#define STRUCTURE_H

#include <iostream>
#include <vector>
#include <string>
#include <utility>      // std::pair


// c++11 alias technique
using nested_double_vec = std::vector<std::vector<double> >;

class Structure{

	private:

	const std::string lattice_type;
	nested_double_vec corner_vecs;
	nested_double_vec base_vecs;

	public:

	Structure();
	Structure(const std::string lt);
	Structure(Structure& s);
	~Structure();

	std::string getLatticeType();

	void initializeVectors(const double& lattice_constant);
	
	std::pair <nested_double_vec,nested_double_vec> getVectors();
	void printVectors();
};

#endif


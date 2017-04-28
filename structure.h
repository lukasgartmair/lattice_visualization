#ifndef STRUCTURE_H
#define STRUCTURE_H

#include <iostream>
#include <vector>
#include <string>

class Structure{

	private:

	const std::string lattice_type;
	std::vector<std::vector<double> > base_vecs;

	public:

	Structure();
	Structure(const std::string lt);
	Structure(Structure& s);
	~Structure();

	std::string getLatticeType();

	void initializeBaseVectors(const double& lattice_constant);

	void getBaseVectors();

};

#endif


#ifndef STRUCTURE_H
#define STRUCTURE_H

#include <iostream>
#include <vector>
#include <string>

class Structure{

	private:

	std::string lattice_type;
	std::vector<std::vector<double> > base_vecs;

	public:

	Structure();
	Structure(std::string lt);
	Structure(Structure& s);
	~Structure();

	enum lattice_types{fcc}	;

	std::string getLatticeType();

	void initializeBaseVectors();

	void getBaseVectors();

};

#endif


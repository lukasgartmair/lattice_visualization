#ifndef ATOM_H
#define ATOM_H

class Atom{

	private:

	const std::string element;
	const double radius_angstroem;

	public:

	Atom();
	Atom(const std::string e);
	Atom(Atom& a);
	~Atom();

	std::string getElement();

};

#endif

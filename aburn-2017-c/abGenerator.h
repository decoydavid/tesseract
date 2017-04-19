#pragma once

class Lattice;

// Override this class to create different lattice behaviours
class Generator
{
public:
	Generator()
	{}
	virtual ~Generator()
	{}

	virtual void Update(Lattice &xLattice);

	virtual UCHAR GenerateValue(Lattice &xLattice, int i, int j, int k)
	{
		return 0;
	}

private:

};
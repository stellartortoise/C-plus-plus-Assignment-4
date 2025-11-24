#ifndef _CITY_H
#define _CITY_H

#include <iostream>
#include "GameSpecs.h"

using namespace std;

class Organism;

class City
{
protected:
	Organism* grid[GRIDSIZE][GRIDSIZE];
	int generation;

public:
	City();
	virtual ~City();

	Organism* getOrganism(int x, int y);
	void setOrganism(Organism* organism, int x, int y);

	void step(); //includes all actions except reset, counting, and printing in this solution.
	void reset();
	int countType(char);
	friend ostream& operator<<(ostream& output, City& city);

	void col(int c);   //for colors
};

#endif


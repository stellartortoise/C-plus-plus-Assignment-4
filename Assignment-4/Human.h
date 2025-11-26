#ifndef _Human_H
#define _Human_H

#include "Organism.h"

class Human : public Organism
{
protected:
	int timeStep = 0;
public:
	Human();
	Human(City* city, int size);
	Human(City* city, int size, int x, int y);
	virtual ~Human();

	bool isSheltered = false;

	void turn(); //all things a human may do on their turn. i.e. a move, and if allowed a recruitment  
};

#endif

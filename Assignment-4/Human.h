#ifndef _Human_H
#define _Human_H

#include "Organism.h"

class Human : public Organism
{
public:
	Human();
	Human(City* city, int size);
	virtual ~Human();

	void turn(); //all things a human may do on their turn. i.e. a move, and if allowed a recruitment  
};

#endif

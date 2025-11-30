#ifndef _Zombie_H
#define _Zombie_H

#include "Organism.h"
#include "GameSpecs.h"

class Zombie : public Organism
{
protected:
	int timeStep =0;
	bool full = false;
	int fullTurns = ZOMBIE_STARVE - 1;
	int starveTurns = 2;
	bool canInfect = false;
	bool canBeCured = false;
public:
	Zombie();
	Zombie(City* city, int size);
	Zombie(City* city, int size, int x, int y);
	virtual ~Zombie();

	void turn(); //all things a zombie may do on their turn. i.e. an eat/move or a regular move, and if allowed a bite or convert back to human 

	bool shouldCure = false;
};

#endif

#ifndef _Zombie_H
#define _Zombie_H

#include "Organism.h"

class Zombie : public Organism
{
public:
	Zombie();
	Zombie(City* city, int size);
	virtual ~Zombie();

	void turn(); //all things a zombie may do on their turn. i.e. an eat/move or a regular move, and if allowed a bite or convert back to human 

};

#endif

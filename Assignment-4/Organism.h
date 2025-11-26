#ifndef _Organism_H
#define _Organism_H

#include <iostream>

using namespace std;

class City;

class Organism
{
protected:
	int x;
	int y;
	int size;
	char type;
	bool moved;
	City* city;

public:
	Organism();
	Organism(City* city, int size);
	Organism(City* city, int size, int x, int y);
	virtual ~Organism();
	virtual void turn() = 0;

	bool getMoved();
	void setMoved(bool _moved);

	int GetX() const { return x; }
	int GetY() const { return y; }

	int SetX(int newX) { x = newX; return x; }
	int SetY(int newY) { y = newY; return y; }

	char getType();

	friend ostream& operator<<(ostream& output, Organism* organism);
};

#endif


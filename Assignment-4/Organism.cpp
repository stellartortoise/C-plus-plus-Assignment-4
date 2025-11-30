#include "Organism.h"
#include "City.h"

Organism::Organism() : x(0), y(0), size(0), type('-'), moved(false), city(nullptr) {}

Organism::Organism(City* city, int size) : x(0), y(0), size(size), type('-'), moved(false), city(city) {}

Organism::Organism(City* city, int size, int x, int y) : x(x), y(y), size(size), type('-'), moved(false), city(city) {}

Organism::~Organism() {}

bool Organism::getMoved() {
	return moved;
}

void Organism::setMoved(bool _moved) {
	moved = _moved;
}

char Organism::getType() {
	return type;
}


ostream& operator<<(ostream& output, Organism* organism) {

	output << organism->type;

	return output;
}
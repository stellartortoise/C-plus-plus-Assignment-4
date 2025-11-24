#include "Organism.h"
#include "City.h"

Organism::Organism() : x(0), y(0), size(0), type(SPACE_CH), moved(false), city(nullptr) {}

Organism::Organism(City* city, int size) : x(0), y(0), size(size), type(SPACE_CH), moved(false), city(city) {}

Organism::Organism(City* city, int size, int x, int y) : x(x), y(y), size(size), type(SPACE_CH), moved(false), city(city) {}

Organism::~Organism() {}

bool Organism::getMoved() {
	return moved;
}

void Organism::setMoved(bool _moved) {
	moved = _moved;
}

bool Organism::getType() {
	return type;
}


ostream& operator<<(ostream& output, Organism* organism) {

	switch (organism->type) {
		
		case HUMAN_CH:
			output << "H";
			break;
		case ZOMBIE_CH:
			output << "Z";
			break;
		case BUILDING_CH:
			output << "B";
			break;
		case SPACE_CH:
			output << "-";
			break;
		default:
			output << "?";
			break;
	}

	return output;
}
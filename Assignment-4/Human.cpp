#include "Human.h"
#include "City.h"

Human::Human() : Organism() 
{
	type = HUMAN_CH;

	city->humans.push_back(this);
}

Human::Human(City* city, int size) : Organism(city, size) 
{
	type = HUMAN_CH;
}

Human::~Human() 
{
	//remove this human from the humans vector in city
	auto& humans = city->humans;
	humans.erase(std::remove(humans.begin(), humans.end(), this), humans.end());
}

void Human::turn() 
{
	// Implement the logic for a human's turn
	// This may include moving and breeding if conditions are met
	// Example move logic (to be replaced with actual implementation)
	// Check for available adjacent spaces and move if possible
	// After moving, check if breeding conditions are met and breed if allowed
	setMoved(true); // Mark as moved for this turn
}
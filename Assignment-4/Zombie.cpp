#include "Zombie.h"
#include "City.h"

Zombie::Zombie() : Organism() 
{
	type = ZOMBIE_CH;

	//add this zombie to the zombies vector in city
	city->zombies.push_back(this);
}

Zombie::Zombie(City* city, int size) : Organism(city, size) 
{
	type = ZOMBIE_CH;
}

Zombie::~Zombie() 
{
	//remove this zombie from the zombies vector in city
	auto& zombies = city->zombies;
	zombies.erase(std::remove(zombies.begin(), zombies.end(), this), zombies.end());
}

void Zombie::turn() 
{
	// Implement the logic for a zombie's turn
	// This may include moving, eating humans, breeding, or starving if conditions are met
	// Example move logic (to be replaced with actual implementation)
	// Check for adjacent humans to eat; if none, check for available adjacent spaces to move
	// After moving or eating, check if breeding conditions are met and breed if allowed
	// Also check if starving conditions are met and convert back to human if necessary
	setMoved(true); // Mark as moved for this turn
}
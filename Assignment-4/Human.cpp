#include "Human.h"
#include "City.h"


Human::Human() : Organism() 
{
	type = 'H';

	city->humans.push_back(this);
}

Human::Human(City* city, int size) : Organism(city, size) 
{
	type = 'H';

	city->humans.push_back(this);
}

Human::Human(City* city, int size, int x, int y) : Organism(city, size, x, y) 
{
	type = 'H';
	city->humans.push_back(this);
}

Human::~Human() 
{
	//remove this human from the humans vector in city
	auto& humans = city->humans;
	humans.erase(std::remove(humans.begin(), humans.end(), this), humans.end());
}

void Human::turn() 
{

	vector<pair<int, int>> freespaces;

	// Movement (Human can move left, right, up, down if space is available)

	// Check adjacent cells for empty space
	if (!city->getOrganism(x - 1, y) && x > 0)
		freespaces.push_back({ x - 1, y });

	if (!city->getOrganism(x + 1, y) && x < GRIDSIZE - 1)
		freespaces.push_back({ x + 1, y });

	if (!city->getOrganism(x, y - 1) && y > 0)
		freespaces.push_back({ x, y - 1 });

	if (!city->getOrganism(x, y + 1) && y < GRIDSIZE - 1)
		freespaces.push_back({ x, y + 1 });

	// If there are free spaces, move to one randomly
	if (!freespaces.empty()) 
	{
		int randIndex = rand() % freespaces.size();
		pair<int, int> newPos = freespaces[randIndex];
		// Update city grid
		city->setOrganism(nullptr, x, y); // Vacate current position
		x = newPos.first;
		y = newPos.second;
		city->setOrganism(this, x, y); // Move to new position
	}

	// Recruiting/Breeding (if conditions are met, recruit a new Human in an adjacent empty cell)

	if (timeStep == 2)
	{
		timeStep = 0;

		// Check adjacent cells for empty space again
		freespaces.clear();

		if (!city->getOrganism(x - 1, y) && x > 0)
			freespaces.push_back({ x - 1, y });

		if (!city->getOrganism(x + 1, y) && x < GRIDSIZE - 1)
			freespaces.push_back({ x + 1, y });

		if (!city->getOrganism(x, y - 1) && y > 0)
			freespaces.push_back({ x, y - 1 });

		if (!city->getOrganism(x, y + 1) && y < GRIDSIZE - 1)
			freespaces.push_back({ x, y + 1 });

		// If there are free spaces, move to one randomly
		if (!freespaces.empty())
		{
			int randIndex = rand() % freespaces.size();
			pair<int, int> newPos = freespaces[randIndex];
			// Spawn Human at new position
			Human* newHuman = new Human(city, 1, newPos.first, newPos.second);
			city->setOrganism(newHuman, newPos.first, newPos.second);
		}
	}
	else
	{
		timeStep++;
	}


	setMoved(true); // Mark as moved for this turn
}

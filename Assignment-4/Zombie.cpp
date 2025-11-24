#include "Zombie.h"
#include "City.h"

Zombie::Zombie() : Organism() 
{
	type = 'Z';

	//add this zombie to the zombies vector in city
	city->zombies.push_back(this);
}

Zombie::Zombie(City* city, int size) : Organism(city, size) 
{
	type = 'Z';

	city->zombies.push_back(this);
}

Zombie::Zombie(City* city, int size, int x, int y) : Organism(city, size, x, y) 
{
	type = 'Z';
	city->zombies.push_back(this);
}

Zombie::~Zombie() 
{
	//remove this zombie from the zombies vector in city
	auto& zombies = city->zombies;
	zombies.erase(std::remove(zombies.begin(), zombies.end(), this), zombies.end());
}

void Zombie::turn() 
{
    using std::pair;
    using std::vector;

    vector<pair<int, int>> humanTargets;
    vector<pair<int, int>> freeSpaces;

    // Directions: up, down, left, right, and diagonals
    int dx[] = { -1, -1, -1, 0, 0, 1, 1, 1 };
    int dy[] = { -1, 0, 1, -1, 1, -1, 0, 1 };

    for (int dir = 0; dir < 8; ++dir) {
        int nx = x + dx[dir];
        int ny = y + dy[dir];

        // Check bounds
        if (nx >= 0 && nx < GRIDSIZE && ny >= 0 && ny < GRIDSIZE) {
            Organism* target = city->getOrganism(nx, ny);
            if (!target) {
                freeSpaces.push_back({ nx, ny });
            } else if (target->getType() == 'H') {
                humanTargets.push_back({ nx, ny });
            }
            // If it's a zombie, do nothing
        }
    }

    // Prioritize moving to a Human if possible
    if (!humanTargets.empty()) {
        int randIndex = rand() % humanTargets.size();
        pair<int, int> newPos = humanTargets[randIndex];
        city->setOrganism(nullptr, x, y); // Vacate current position
        x = newPos.first;
        y = newPos.second;
        Organism* eaten = city->getOrganism(x, y);
        delete eaten; // Remove the human from memory
        city->setOrganism(this, x, y); // Move to new position
    } else if (!freeSpaces.empty()) {
        int randIndex = rand() % freeSpaces.size();
        pair<int, int> newPos = freeSpaces[randIndex];
        city->setOrganism(nullptr, x, y); // Vacate current position
        x = newPos.first;
        y = newPos.second;
        city->setOrganism(this, x, y); // Move to new position
    }

    setMoved(true); // Mark as moved for this turn
}
#include "Zombie.h"
#include "City.h"

Zombie::Zombie() : Organism() 
{
	type = 'Z';

	//add this zombie to the zombies vector in city
	city->zombies.push_back(this);

    canBeCured = city->zombiesCanStarve;
}

Zombie::Zombie(City* city, int size) : Organism(city, size) 
{
	type = 'Z';

	city->zombies.push_back(this);

	canBeCured = city->zombiesCanStarve;
}

Zombie::Zombie(City* city, int size, int x, int y) : Organism(city, size, x, y) 
{
	type = 'Z';
	city->zombies.push_back(this);

    canBeCured = city->zombiesCanStarve;
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

    if (canInfect)
    {
        // Check adjacent cells for empty space again
        freeSpaces.clear();
        humanTargets.clear();

        // Directions: up, down, left, right, and diagonals
        int dx[] = { -1, -1, -1, 0, 0, 1, 1, 1 };
        int dy[] = { -1, 0, 1, -1, 1, -1, 0, 1 };

        for (int dir = 0; dir < 8; ++dir) {
            int nx = x + dx[dir];
            int ny = y + dy[dir];

            // Check bounds
            if (nx >= 0 && nx < GRIDSIZE && ny >= 0 && ny < GRIDSIZE)
            {
                Organism* target = city->getOrganism(nx, ny);
                if (target != nullptr)
                {
                    //continue; // Cell is occupied

                    if (target->getType() == 'H') {
                        humanTargets.push_back({ nx, ny });
                    }
                    // If it's a zombie, do nothing
                }
            }
        }

        if (!humanTargets.empty())
        {
            int randIndex = rand() % humanTargets.size();
            pair<int, int> newPos = humanTargets[randIndex];

            // Get the Human at the target position
            Organism* infected = city->getOrganism(newPos.first, newPos.second);
            if (infected != nullptr)
            {
                delete infected;
                city->setOrganism(nullptr, newPos.first, newPos.second);
                Zombie* newZombie = new Zombie(city, 1, newPos.first, newPos.second);
                city->setOrganism(newZombie, newPos.first, newPos.second);
				canInfect = false; 
            }
        }
    }

    // Directions: up, down, left, right, and diagonals
    int dx[] = { -1, -1, -1, 0, 0, 1, 1, 1 };
    int dy[] = { -1, 0, 1, -1, 1, -1, 0, 1 };

    for (int dir = 0; dir < 8; ++dir) 
    {
        int nx = x + dx[dir];
        int ny = y + dy[dir];

        // Check bounds
        if (nx >= 0 && nx < GRIDSIZE && ny >= 0 && ny < GRIDSIZE) 
        {
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
    if (!humanTargets.empty()) 
    {
        int randIndex = rand() % humanTargets.size();
        pair<int, int> newPos = humanTargets[randIndex];
        city->setOrganism(nullptr, x, y); // Vacate current position
        x = newPos.first;
        y = newPos.second;
        Organism* eaten = city->getOrganism(x, y);
        delete eaten; // Still delete via base pointer
        city->setOrganism(nullptr, x, y);
        city->setOrganism(this, x, y); // Move to new position
		full = true; 
    } 
    else if (!freeSpaces.empty()) 
    {
        int randIndex = rand() % freeSpaces.size();
        pair<int, int> newPos = freeSpaces[randIndex];
        city->setOrganism(nullptr, x, y); // Vacate current position
        x = newPos.first;
        y = newPos.second;
        city->setOrganism(this, x, y); // Move to new position
    }

    // After movement/eating logic
    if (full) {
        fullTurns++;
        if (fullTurns >= ZOMBIE_STARVE) {
            full = false;
            fullTurns = 0;
        }
    }

    if (!full && timeStep == ZOMBIE_STARVE) {
        if (canBeCured) 
        {
            shouldCure = true;
        } else 
        {
            // Starve to death
            city->setOrganism(nullptr, x, y);
            setMoved(true);
            delete this;
            return; // Exit as this zombie is deleted
		}
    }


    //"Breeding"

    if (timeStep == ZOMBIE_BREED)
    {
        timeStep = 0;
		canInfect = true;
    }
    else
    {
        timeStep++;
    }


    setMoved(true); // Mark as moved for this turn

}
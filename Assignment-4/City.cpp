#include "City.h"
#include "Organism.h" // Add this include to fix incomplete type error
#include <vector>
#include "Human.h"
#include "Zombie.h"
#include <iomanip>
#include <windows.h>
#include <ctime>

//vector<Human> humans;
//vector<Zombie> zombies;

City::City() : generation(0) 
{
	std::srand(static_cast<unsigned>(std::time(0)));

	int startHumans = HUMAN_STARTCOUNT;
	int startZombies = ZOMBIE_STARTCOUNT;

	while (startHumans > 0) 
	{
		int hx = rand() % GRIDSIZE;
		int hy = rand() % GRIDSIZE;
		if (grid[hx][hy] == nullptr) 
		{
			Human* human = new Human(this, 1, hx, hy);
			grid[hx][hy] = human;
			startHumans--;
		}
	}

	while (startZombies > 0) 
	{
		int zx = rand() % GRIDSIZE;
		int zy = rand() % GRIDSIZE;
		if (grid[zx][zy] == nullptr) 
		{
			Zombie* zombie = new Zombie(this, 1, zx, zy);
			grid[zx][zy] = zombie;
			startZombies--;
		}
	}

	// Initialize the grid with nullptrs or empty spaces
	//for (int i = 0; i < GRIDSIZE; ++i) 
	//{
	//	for (int j = 0; j < GRIDSIZE; ++j) 
	//	{
	//		//Randomly populate the grid with Humans and Zombies or spaces
	//		if (rand() % 100 < 20) // 20% chance to place a Human
	//		{
	//			Human* human = new Human(this, 1, i, j);
	//			grid[i][j] = human;
	//		} 
	//		else if (rand() % 100 < 20) // 5% chance to place a Zombie
	//		{
	//			Zombie* zombie = new Zombie(this, 1, i, j);
	//			grid[i][j] = zombie;
	//		} 
	//		else 
	//		{
	//			grid[i][j] = nullptr; // Empty space
	//		}
	//		
	//	}
	//}
}

City::~City() 
{
	// Clean up dynamically allocated organisms
	for (int i = 0; i < GRIDSIZE; ++i) 
	{
		for (int j = 0; j < GRIDSIZE; ++j) 
		{
			delete grid[i][j];
		}
	}
}

Organism* City::getOrganism(int x, int y) 
{
	return grid[x][y];
}

void City::setOrganism(Organism* organism, int x, int y)
{
	grid[x][y] = organism;
}

void City::step() {
	// Implement the logic to perform a step in the simulation
	// This typically involves calling the turn method of each organism
	for (int i = 0; i < GRIDSIZE; ++i) 
	{
		for (int j = 0; j < GRIDSIZE; ++j) 
		{
			if (grid[i][j] != nullptr && !grid[i][j]->getMoved()) 
			{
				grid[i][j]->turn();
			}
		}
	}
	cureZombies();
	generation++;
}

void City::reset() 
{
	// Reset the moved status of all organisms
	for (int i = 0; i < GRIDSIZE; ++i) 
	{
		for (int j = 0; j < GRIDSIZE; ++j) 
		{
			if (grid[i][j] != nullptr) 
			{
				grid[i][j]->setMoved(false);
			}
		}
	}
}

int City::countType(char type) 
{
	int count = 0;
	
	switch (type) 
	{
		case 'H':
			count = humans.size();
			break;
		case 'Z':
			count = zombies.size();
			break;
		default:
			count = 0;
			break;
	}

	return count;
}

void City::col(int c)
{
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsole, c);
}

ostream& operator<<(ostream& output, City& city) 
{
    for (int i = 0; i < GRIDSIZE; ++i) 
	{
        for (int j = 0; j < GRIDSIZE; ++j) 
		{
			city.col(city.grid[i][j] ? (city.grid[i][j]->getType() == 'H' ? HUMAN_COLOR : ZOMBIE_COLOR) : DASH_COLOR);
            output << std::setw(2) << (city.grid[i][j] ? city.grid[i][j]->getType() : '-');
        }
        output << endl;
    }
    return output;
}

bool City::hasDiversity() 
{
	bool hasHumans = false;
	bool hasZombies = false;

	humans.size() > 0 ? hasHumans = true : hasHumans = false;
	zombies.size() > 0 ? hasZombies = true : hasZombies = false;

	if (hasHumans && hasZombies) 
	{
		return true;
	}

	return false;
}

void City::countOrganisms(char type) 
{
	/*int count = humans.size() + zombies.size();
	*/

	int count = 0;

	switch (type)
	{
	case 'H':
		count = humans.size();
		break;
	case 'Z':
		count = zombies.size();
		break;
	default:
		count = 0;
		break;
	}

	cout << "Count of type " << type << ": " << count << endl;
}

int City::getGeneration() { return generation; }

void City::cureZombies()
{
	for (int i = 0; i < GRIDSIZE; ++i) {
		for (int j = 0; j < GRIDSIZE; ++j) {
			Zombie* zombie = dynamic_cast<Zombie*>(grid[i][j]);
			if (zombie && zombie->shouldCure) {
				delete zombie;
				zombie = nullptr;
				grid[i][j] = new Human(this, 1, i, j);
			}
		}
	}
}
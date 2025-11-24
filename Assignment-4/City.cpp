#include "City.h"
#include "Organism.h" // Add this include to fix incomplete type error
#include <vector>
#include "Human.h"
#include "Zombie.h"

vector<Human> humans;
vector<Zombie> zombies;

City::City() : generation(0) 
{
	// Initialize the grid with nullptrs or empty spaces
	for (int i = 0; i < GRIDSIZE; ++i) 
	{
		for (int j = 0; j < GRIDSIZE; ++j) 
		{
			grid[i][j] = nullptr; // or new Space() if you have a Space class
		}
	}
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
	for (int i = 0; i < GRIDSIZE; ++i) 
	{
		for (int j = 0; j < GRIDSIZE; ++j) 
		{
			if (grid[i][j] != nullptr && grid[i][j]->getType() == type)
			{
				count++;
			}
		}
	}
	return count;
}

ostream& operator<<(ostream& output, City& city) 
{
	for (int i = 0; i < GRIDSIZE; ++i) 
	{
		for (int j = 0; j < GRIDSIZE; ++j) 
		{
			if (city.grid[i][j] != nullptr) 
			{
				output << city.grid[i][j];
			} 
			else 
			{
				output << "-"; // or appropriate representation for empty space
			}
		}
		output << endl;
	}
	return output;
}

void City::col(int c) 
{
	
}

bool City::hasDiversity() 
{
	bool hasHumans = false;
	bool hasZombies = false;

	for (int i = 0; i < GRIDSIZE; ++i) 
	{
		for (int j = 0; j < GRIDSIZE; ++j) 
		{
			if (grid[i][j] != nullptr)
			{
				if (grid[i][j]->getType() == HUMAN_CH)
				{
					hasHumans = true;
				}
				else if (grid[i][j]->getType() == ZOMBIE_CH)
				{
					hasZombies = true;
				}
			}
			if (hasHumans && hasZombies) 
			{
				return true;
			}
		}
	}

	return false;
}

void City::countOrganisms(char type) 
{
	int count = 0;
	for (int i = 0; i < GRIDSIZE; ++i) 
	{
		for (int j = 0; j < GRIDSIZE; ++j) 
		{
			if (grid[i][j] != nullptr && grid[i][j]->getType() == type)
			{
				count++;
			}
		}
	}
	cout << "Count of type " << type << ": " << count << endl;
}

int City::getGeneration() { return generation; }
#ifndef _CITY_H
#define _CITY_H

#include <iostream>
#include "GameSpecs.h"
#include <vector>

using namespace std;

// Forward declarations
class Organism;
class Human;
class Zombie;

class City
{
protected:
    Organism* grid[GRIDSIZE][GRIDSIZE];
    int generation;

public:
    City();
    virtual ~City();

    void CitySetup(bool _zombiesCurable, bool _buildingsExist);

    Organism* getOrganism(int x, int y);
    void setOrganism(Organism* organism, int x, int y);

    void step();
    void reset();
    int countType(char);
    friend ostream& operator<<(ostream& output, City& city);

    void col(int c);

    bool hasDiversity();
    void countOrganisms(char type);
    int getGeneration();
    void cureZombies();

    vector<Human*> humans;
    vector<Zombie*> zombies;

    bool zombiesCanStarve = false;
    bool buildingsExist = false;
};

#endif


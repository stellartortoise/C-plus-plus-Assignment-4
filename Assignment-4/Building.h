#ifndef _Building_H
#define _Building_H

#include "Organism.h"
#include "Human.h"
#include <vector>
#include "City.h"

class Building : public Organism
{
protected:
    int maxCapacity = 1;
    std::vector<Human*> shelteredHumans; // moved into the class (per-building)
public:
    Building();
    Building(City* city, int size);
    Building(City* city, int size, int x, int y);
    virtual ~Building();
    void shelterHuman(Human* shelteree); // shelters a human if capacity allows
    void releaseHuman();                  // releases one sheltered human if any
    bool isOccupied();                    // true if at least one human is sheltered
    void turn();
};

#endif


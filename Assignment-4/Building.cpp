#include "Building.h"
#include "City.h"
#include <cstdlib>

Building::Building() : Organism()
{
    type = 'B';
}

Building::Building(City* city, int size) : Organism(city, size)
{
    type = 'B';
}

Building::Building(City* city, int size, int x, int y) : Organism(city, size, x, y)
{
    type = 'B';
}

Building::~Building()
{
    // No dynamic memory to clean up in Building
}

void Building::shelterHuman(Human* shelteree)
{
    if (shelteree && shelteredHumans.size() < (size_t)maxCapacity)
    {
        shelteredHumans.push_back(shelteree);
        shelteree->isSheltered = true;
        // remove human from the grid
        city->setOrganism(nullptr, shelteree->GetX(), shelteree->GetY());
    }
}

void Building::releaseHuman()
{
    if (!shelteredHumans.empty())
    {
        Human* releasedHuman = shelteredHumans.back();
        shelteredHumans.pop_back();
        releasedHuman->isSheltered = false;

        // find a nearby empty cell to place the human back
        std::vector<std::pair<int,int>> freeSpaces;
        if (x > 0 && !city->getOrganism(x - 1, y))               freeSpaces.push_back({x - 1, y});
        if (x < GRIDSIZE - 1 && !city->getOrganism(x + 1, y))    freeSpaces.push_back({x + 1, y});
        if (y > 0 && !city->getOrganism(x, y - 1))               freeSpaces.push_back({x, y - 1});
        if (y < GRIDSIZE - 1 && !city->getOrganism(x, y + 1))    freeSpaces.push_back({x, y + 1});

        if (x > 0 && y > 0 && !city->getOrganism(x - 1, y - 1))                               freeSpaces.push_back({x - 1, y - 1});
        if (x > 0 && y < GRIDSIZE - 1 && !city->getOrganism(x - 1, y + 1))                    freeSpaces.push_back({x - 1, y + 1});
        if (x < GRIDSIZE - 1 && y > 0 && !city->getOrganism(x + 1, y - 1))                    freeSpaces.push_back({x + 1, y - 1});
        if (x < GRIDSIZE - 1 && y < GRIDSIZE - 1 && !city->getOrganism(x + 1, y + 1))         freeSpaces.push_back({x + 1, y + 1});

        if (!freeSpaces.empty())
        {
            int randIndex = rand() % (int)freeSpaces.size();
            auto newPos = freeSpaces[randIndex];
            releasedHuman->SetX(newPos.first);
            releasedHuman->SetY(newPos.second);
            city->setOrganism(releasedHuman, newPos.first, newPos.second);
        }
        else
        {
            // No space to release; keep sheltered (so state remains consistent)
            releasedHuman->isSheltered = true;
            shelteredHumans.push_back(releasedHuman);
        }
    }
}

void Building::turn()
{
    int stayPercentage = 50; // 50% chance to stay sheltered

    bool didRelease = false;
    if (!shelteredHumans.empty())
    {
        int roll = rand() % 100;
        if (roll >= stayPercentage)
        {
            size_t before = shelteredHumans.size();
            releaseHuman();
            didRelease = (shelteredHumans.size() < before);
        }
    }

    // If we released this turn, don't immediately shelter again (lets UI show blue)
    if (!didRelease && shelteredHumans.size() < (size_t)maxCapacity)
    {
        // check all 8 neighbors for a human (not empty)
        int dx[] = { -1, -1, -1, 0, 0, 1, 1, 1 };
        int dy[] = { -1,  0,  1,-1, 1,-1, 0, 1 };

        std::vector<std::pair<int,int>> humanNeighbors;

        for (int dir = 0; dir < 8; ++dir)
        {
            int nx = x + dx[dir];
            int ny = y + dy[dir];
            if (nx >= 0 && nx < GRIDSIZE && ny >= 0 && ny < GRIDSIZE)
            {
                Organism* occ = city->getOrganism(nx, ny);
                if (occ && occ->getType() == 'H')
                {
                    humanNeighbors.push_back({nx, ny});
                }
            }
        }

        if (!humanNeighbors.empty())
        {
            int index = rand() % (int)humanNeighbors.size();
            auto position = humanNeighbors[index];
            Organism* occupier = city->getOrganism(position.first, position.second);
            if (occupier && occupier->getType() == 'H')
            {
                if (Human* human = (Human*)occupier)
                {
                    shelterHuman(human);
                }
            }
        }
    }

    setMoved(true);
}

bool Building::isOccupied()
{
    return !shelteredHumans.empty();
}

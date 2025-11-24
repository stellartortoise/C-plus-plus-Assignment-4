//
// Created by W0487099 on 11/24/2025.
//
//Example main.cpp
//This supposes that city->step() calls the move method of each organism in the city
//in a single pass causing each to perform all tasks that it can.

#include <iostream>
#include <chrono>
#include <thread>
#include "Organism.h"
#include "City.h"
#include "GameSpecs.h"
#include "Human.h"

using namespace std;

void ClearScreen()
{
    cout << "\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n";
}

int main() {
    City* city = new City();
    chrono::milliseconds interval(INTERVAL);

    while (city->hasDiversity()) { //while both humans and zombies exist
        this_thread::sleep_for(interval);
        ClearScreen();
        city->step();
        city->reset(); //resets moved flags
        city->countOrganisms('H');// run once for each type
        cout << *city; //prints city
        cout << "GENERATION " << city->getGeneration() << endl;
        cout << "HUMANS: " << city->countType(HUMAN_CH) << endl;
        cout << "ZOMBIES: " << city->countType(ZOMBIE_CH) << endl;
    }//end while
}//end main
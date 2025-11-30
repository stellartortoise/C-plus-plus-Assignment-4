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
	system("CLS");
    //cout << "\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n";
}

void SetUp(City* city) 
{
	cout << "ZOMBIES VS HUMANS SIMULATION" << endl;
	cout << "============================" << endl;

	cout << "Humans (H) try to survive by breeding and seeking shelter in buildings (B)." << endl;
	cout << "Zombies (Z) hunt Humans to infect them and convert them into more Zombies." << endl;

	cout << "The simulation runs until either all Humans are infected (ELE) or a balanced state is achieved after " << ITERATIONS << " generations.\n" << endl;
      
	cout << "Should Zombies be cured after starving? (y/n): " << endl;
	char response;
	cin >> response;
    if (response == 'y' || response == 'Y') 
    {
        cout << "Zombies will be cured after starving.\n" << endl;
		city->zombiesCanStarve = true;
    } 
    else 
    {
        cout << "Zombies will NOT be cured after starving.\n" << endl;
		city->zombiesCanStarve = false;
    }

	cout << "Should buildings exist for Humans to take shelter in? (y/n): " << endl;
    cin >> response;
    if (response == 'y' || response == 'Y') 
    {
		cout << "Buildings exist.\n" << endl;
		city->buildingsExist = true;
    } 
    else
    {
        cout << "There are no buildings.\n" << endl;
		city->buildingsExist = false;
    }

	city->CitySetup(city->zombiesCanStarve, city->buildingsExist);
}

int main() {
    City* city = new City();
    chrono::milliseconds interval(INTERVAL);

	SetUp(city);
	ClearScreen();

    while (city->hasDiversity() && city->getGeneration() < ITERATIONS) { //while both humans and zombies exist
        this_thread::sleep_for(interval);
        ClearScreen();
        city->step();
        city->reset(); //resets moved flags
        city->countOrganisms('H');// run once for each type
        city->countOrganisms('Z');// run once for each type
        cout << *city; //prints city
        city->col(15); //set color to bright white for output
        cout << "GENERATION " << city->getGeneration() << endl;
        cout << "HUMANS: " << city->countType('H') << endl;
        cout << "ZOMBIES: " << city->countType('Z') << endl;
		cout << "\n" << endl;
		cout << "Zombies Can be Cured?: " << (city->zombiesCanStarve ? "Yes" : "No") << endl;
		cout << "Buildings Exist?: " << (city->buildingsExist ? "Yes" : "No") << endl;
    }//end while

    if (city->getGeneration() >= ITERATIONS) {
		city->col(10); //set color to bright green for success message
        cout << "SUCCESS! Balanced Simulation Achieved." << endl;
    } else {
		city->col(12); //set color to bright red for failure message
        cout << "FAIL! ELE Occured." << endl;
	}
	//reset color to default
    city->col(15); //set color to bright white for output

	cout << "Run again? (y/n): " << endl;
	char response;
	cin >> response;
    if (response == 'y' || response == 'Y') {
        delete city;
        ClearScreen();
        main(); //restart the simulation
    } else {
        delete city;
        return 0;
	}
}//end main
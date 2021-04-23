#include <iostream>
#include <random>
#include "Building.h"
#include "GlobalClock.h"
#include "Elevator.h"
#include "Scheduler.h"

using namespace std;

int main() {
	// Global clock declaration
	//Clock clk;
	srand(time(0));

	// Create vector of floors for the building ERC
	// With floors 3-8
	vector<Floor> floors;
	floors.push_back(Floor(3));
	floors.push_back(Floor(4));
	floors.push_back(Floor(5));
	floors.push_back(Floor(6));
	floors.push_back(Floor(7));
	floors.push_back(Floor(8));

	// Create a building object for ERC with the above floors
	Building* ERC = new Building("ERC", floors);

	// Create elevator servicing ERC
	Elevator elevator = Elevator(ERC);
	
	// Create vector of Person objects to send into simulator
	vector<Person> people;
	people.push_back(Person(6, 3));
	people.push_back(Person(8, 3));
	people.push_back(Person(3, 6));
	people.push_back(Person(4, 7));
	people.push_back(Person(6, 4));
	people.push_back(Person(5, 3));
	people.push_back(Person(7, 3));
	people.push_back(Person(4, 7));
	people.push_back(Person(3, 8));
	people.push_back(Person(3, 5));

	// Create Scheduler and send in vector of Persons
	Scheduler scheduler = Scheduler(ERC, people);

	scheduler.sendPerson();
	scheduler.sendPerson();
	scheduler.sendPerson();
	scheduler.sendPerson();
	scheduler.sendPerson();
	scheduler.sendPerson();
	scheduler.sendPerson();
	scheduler.sendPerson();
	scheduler.sendPerson();
	scheduler.sendPerson();

	// Run sim

	elevator.getDoor().openDoor();
	while (elevator.numServed() < 3) {
		elevator.load();
		elevator.getDoor().closeDoor();
		clk.advanceTime(1);
		while (!elevator.stopAtFloor()) {
			elevator.advanceFloor();
		}
		clk.advanceTime(1);
		elevator.getDoor().openDoor();
		elevator.unload();
	}
	elevator.getDoor().closeDoor();

	cout << elevator.getAvgWait();

	delete ERC;

	return 0;
}
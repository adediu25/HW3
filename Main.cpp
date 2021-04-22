#include <iostream>
#include "Building.h"
#include "Clock.h"
#include "Elevator.h"
#include "Scheduler.h"

using namespace std;

int main() {
	// Global clock declaration
	Clock clk;

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
	people.push_back(Person(6, 5));

	// Create Scheduler and send in vector of Persons
	Scheduler scheduler = Scheduler(ERC, people);

	scheduler.sendPerson();
	//ERC->getFloor(3).addPerson(people[0]);
	//ERC->getFloor(3).addPerson(people[1]);
	cout << ERC->getFloor(3).removePerson().getDest() << endl;
	//cout << ERC.getFloor(3).removePerson().getDest() << endl;

	delete ERC;

	return 0;
}
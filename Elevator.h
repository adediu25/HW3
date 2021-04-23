#pragma once
#include <queue>
#include "Person.h"
#include "Door.h"
#include "Building.h"

const int MAX_CAPACITY = 5;

class Elevator {
public:
	Building* building;
	int currentFloor;
	bool isGoingUp;
	std::priority_queue<Person> upQueue;
	std::priority_queue<Person> downQueue;
	Door door;
public:
	Elevator(Building*);
	int getFloor() const;
	void nextFloor();
	void enterPerson(Person);
	Person exitPerson();
	bool isFull() const;
	void advanceFloor();
	void updateQueues();
	void load();
	void unload();
	bool stopAtFloor() const;
};
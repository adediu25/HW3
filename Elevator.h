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
	int totalWait;
	int totalPass;
public:
	Elevator(Building*);
	int getFloor() const;
	Door& getDoor();
	void enterPerson(Person);
	Person exitPerson();
	bool isFull() const;
	void advanceFloor();
	void updateQueues();
	void load();
	void unload();
	bool stopAtFloor() const;
	float getAvgWait() const;
	int numServed() const;
};
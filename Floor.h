#pragma once
#include <queue>
#include "Button.h"
#include "Person.h"

class Floor {
private:
	int floorNum;
	std::queue<Person> elevatorQueue;
	Button button;
public:
	Floor(int);
	int getFloorNum() const;
	Button& getButton();
	void addPerson(const Person&);
	Person removePerson();
};
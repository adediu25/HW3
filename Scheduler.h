#pragma once
#include "Building.h"

class Scheduler {
private:
	Building* building;
	std::vector<Person> personList;
	int pIdx;
public:
	Scheduler(Building*, const std::vector<Person> &);
	void sendPerson();
};
#include "Scheduler.h"

Scheduler::Scheduler(Building* bld, const std::vector<Person>& pLst)
{
	personList = pLst;
	building = bld;
	pIdx = 0;
}

void Scheduler::sendPerson()
{
	building->getFloor(personList[pIdx].getFloor()).addPerson(personList[pIdx]);
	++pIdx;
}

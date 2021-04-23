#include "Scheduler.h"
#include "GlobalClock.h"

Scheduler::Scheduler(Building* bld, const std::vector<Person>& pLst)
{
	personList = pLst;
	building = bld;
	pIdx = 0;
}

// Add next Person from list to the queue in their start Floor

void Scheduler::sendPerson()
{
	if (pIdx >= personList.size())
		return;
	personList[pIdx].setTime(clk.getTime());
	building->getFloor(personList[pIdx].getFloor()).addPerson(personList[pIdx]);
	++pIdx;
}

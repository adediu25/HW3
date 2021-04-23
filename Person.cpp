#include "Person.h"
#include "GlobalClock.h"
#include <cmath>

Person::Person(int destNum, int floorNum)
{
	destFloor = destNum;
	currFloor = floorNum;
	startTime = clk.getTime();
}

Person::Person()
{
	currFloor = 0;
	destFloor = 0;
}

void Person::setFloor(int flr)
{
	currFloor = flr;
}

int Person::getDest() const
{
	return destFloor;
}

int Person::getFloor() const
{
	return currFloor;
}

int Person::getTime() const
{
	return startTime;
}

bool Person::operator>(const Person& right) const
{
	int distLeft = abs(this->currFloor - this->destFloor);
	int distRight = abs(right.currFloor - right.destFloor);
		return distLeft < distRight;
}

bool Person::operator<(const Person& right) const
{
	int distLeft = abs(this->currFloor - this->destFloor);
	int distRight = abs(right.currFloor - right.destFloor);
		return distLeft > distRight;
}
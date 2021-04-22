#include "Person.h"
#include <cmath>

Person::Person(int destNum, int floorNum)
{
	destFloor = destNum;
	currFloor = floorNum;
}

Person::Person()
{
	currFloor = 0;
	destFloor = 0;
}

int Person::getDest() const
{
	return destFloor;
}

int Person::getFloor() const
{
	return currFloor;
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
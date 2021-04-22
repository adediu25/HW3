#include "Elevator.h"

Elevator::Elevator(Building* bld)
{
	building = bld;
	currentFloor = building->getBottom();
	isGoingUp = true;
	door = Door();
}

int Elevator::getFloor() const
{
	return currentFloor;
}

void Elevator::nextFloor()
{
	if (isGoingUp) {
		int nextDest = upQueue.top().getDest();
		++currentFloor;
		while (true) {
			if (currentFloor == nextDest)
				door.openDoor();
				while (upQueue.top().getDest() == currentFloor) {

				}
				door.closeDoor();
				break;
			if (isFull()) {
				++currentFloor;
				continue;
			}
			if (building->getFloor(currentFloor).getButton().isActive()) {

			}
		}
	}
	else {

	}
}

void Elevator::enterPerson(Person person)
{
	// Determine if person must go up or down
	if (person.getDest() - person.getFloor() > 0)
		upQueue.push(person);
	else
		downQueue.push(person);
}

Person Elevator::exitPerson()
{
	if (isGoingUp) {
		Person p = upQueue.top();
		upQueue.pop();
		return p;
	}
	else {
		Person p = downQueue.top();
		downQueue.pop();
		return p;
	}
}

bool Elevator::isFull()
{
	return upQueue.size() + downQueue.size() > MAX_CAPACITY;
}

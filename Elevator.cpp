#include "Elevator.h"
#include "GlobalClock.h"
#include <iostream>

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
	int nextDest;
	if (isGoingUp) {
		
		if (!upQueue.empty())
			nextDest = upQueue.top().getDest();
		else
			nextDest = 8;
		//++currentFloor;
		while (true) {
			if (currentFloor == nextDest) {
				door.openDoor();
				while (upQueue.top().getDest() == currentFloor) {
					std::cout << "Person reached destination after wating for time; " << clk.getTime() - exitPerson().getTime() << std::endl;
				}
				door.closeDoor();
				if (upQueue.empty())
					isGoingUp = false;
				break;
			}
			if (isFull()) {
				++currentFloor;
				continue;
			}
			if (building->getFloor(currentFloor).getButton().isActive()) {
				while (!isFull() && building->getFloor(currentFloor).getButton().isActive())
					enterPerson(building->getFloor(currentFloor).removePerson());
				++currentFloor;
			}
		}
	}
	else {
		if (!downQueue.empty())
			nextDest = downQueue.top().getDest();
		else
			nextDest = 3;
		--currentFloor;
		while (true) {
			if (currentFloor == nextDest) {
				door.openDoor();
				while (upQueue.top().getDest() == currentFloor) {
					std::cout << "Person reached destination after wating for time; " << clk.getTime() - exitPerson().getTime() << std::endl;
				}
				door.closeDoor();
				if (downQueue.empty())
					isGoingUp = true;
				break;
			}
			if (isFull()) {
				--currentFloor;
				continue;
			}
			if (building->getFloor(currentFloor).getButton().isActive()) {
				while (!isFull() && building->getFloor(currentFloor).getButton().isActive())
					enterPerson(building->getFloor(currentFloor).removePerson());
				--currentFloor;
			}
		}
	}
}

void Elevator::enterPerson(Person person)
{
	// Determine if person must go up or down,
	// then place them in the respective priority queue

	if (person.getDest() - person.getFloor() > 0)
		upQueue.push(person);
	else
		downQueue.push(person);
}

Person Elevator::exitPerson()
{
	// Remove passenger from respective queue,
	// advance time for exiting passenger

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

bool Elevator::isFull() const
{
	return upQueue.size() + downQueue.size() > MAX_CAPACITY;
}

void Elevator::advanceFloor()
{
	if (isGoingUp) {
		if (currentFloor == 8) {
			isGoingUp = false;
			--currentFloor;
		}
		else
			++currentFloor;
	}
	else {
		if (currentFloor == 3) {
			isGoingUp = true;
			++currentFloor;
		}
		else
			--currentFloor;
	}
	updateQueues();
}

void Elevator::updateQueues()
{
	std::priority_queue<Person> tempQueue;
	while (!upQueue.empty()) {
		Person p = upQueue.top();
		p.setFloor(currentFloor);
		tempQueue.push(p);
	}
	upQueue.swap(tempQueue);
	while (!downQueue.empty()) {
		Person p = downQueue.top();
		p.setFloor(currentFloor);
		tempQueue.push(p);
	}
	downQueue.swap(tempQueue);
}

void Elevator::load()
{
	while (!isFull() && building->getFloor(currentFloor).getButton().isActive()) {
		enterPerson(building->getFloor(currentFloor).removePerson());
		clk.advanceTime(1);
	}
}

void Elevator::unload()
{
	if (isGoingUp) {
		while (!upQueue.empty() && upQueue.top().getDest() == currentFloor) {
			clk.advanceTime(1);
			std::cout << "Person reached destination after wating for time: " << clk.getTime() - exitPerson().getTime() << std::endl;
		}
	}
	else {
		while (!downQueue.empty() && downQueue.top().getDest() == currentFloor) {
			clk.advanceTime(1);
			std::cout << "Person reached destination after wating for time: " << clk.getTime() - exitPerson().getTime() << std::endl;
		}
	}
}

bool Elevator::stopAtFloor() const
{
	if (isFull())
		return false;

	if (isGoingUp) {
		if (!upQueue.empty() && upQueue.top().getDest() == currentFloor)
			return true;
	}
	else {
		if (!downQueue.empty() && downQueue.top().getDest() == currentFloor)
			return true;
	}

	if (building->getFloor(currentFloor).getButton().isActive())
		return true;

	return false;
}

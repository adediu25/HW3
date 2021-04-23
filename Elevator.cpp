#include "Elevator.h"
#include "GlobalClock.h"
#include <iostream>

Elevator::Elevator(Building* bld)
{
	building = bld;
	currentFloor = building->getBottom();
	isGoingUp = true;
	door = Door();
	totalPass = 0;
	totalWait = 0;
}

int Elevator::getFloor() const
{
	return currentFloor;
}

Door& Elevator::getDoor()
{
	return door;
}

// Determine if person must go up or down,
// then place them in the respective priority queue

void Elevator::enterPerson(Person person)
{
	if (person.getDest() - person.getFloor() > 0)
		upQueue.push(person);
	else
		downQueue.push(person);
}

// Remove passenger from respective queue.

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

// Determines if elevator is full based on
// MAX_CAPACITY

bool Elevator::isFull() const
{
	return upQueue.size() + downQueue.size() > MAX_CAPACITY;
}

// Advances elevator one floor and updates 
// the priority queues

void Elevator::advanceFloor()
{
	if (isGoingUp) {
		// If the elevator is at the top floor
		// it turns around
		if (currentFloor == building->getTop()) {
			isGoingUp = false;
			--currentFloor;
		}
		else
			++currentFloor;
	}
	else {
		// If the elevator is at the bottom floor
		// it turns around
		if (currentFloor == building->getBottom()) {
			isGoingUp = true;
			++currentFloor;
		}
		else
			--currentFloor;
	}
	clk.advanceTime(2);
	updateQueues();
}

// Updates priority queues so that order remains 
// true if more passangers board on other floors

void Elevator::updateQueues()
{
	std::priority_queue<Person> tempQueue;
	while (!upQueue.empty()) {
		Person p = upQueue.top();
		p.setFloor(currentFloor);
		tempQueue.push(p);
		upQueue.pop();
	}
	upQueue.swap(tempQueue);
	while (!downQueue.empty()) {
		Person p = downQueue.top();
		p.setFloor(currentFloor);
		tempQueue.push(p);
		downQueue.pop();
	}
	downQueue.swap(tempQueue);
}

// Loads the elevator from current floor

void Elevator::load()
{
	// Passangers enter elevator until it is full
	// or there are no more people on the floor
	while (!isFull() && building->getFloor(currentFloor).getButton().isActive()) {
		enterPerson(building->getFloor(currentFloor).removePerson());
		clk.advanceTime(1);
	}
}

// Unloads passangers at current floor, also
// updates data for average wait time

void Elevator::unload()
{
	if (isGoingUp) {
		/*if (upQueue.empty())
			return;*/
		// passengers exit until there are no more
		// for the given destination floor or until
		// queue is empty
		while (!upQueue.empty() && upQueue.top().getDest() == currentFloor) {
			clk.advanceTime(1);
			// Difference between time when Person 
			// enters queue and time when Person
			// reaches destination
			int x = clk.getTime() - exitPerson().getTime();
			++totalPass;
			totalWait += x;
			std::cout << "Person reached destination after wating for time: " << x << std::endl;
		}
	}
	else {
		/*if (upQueue.empty())
			return;*/
		while (!downQueue.empty() && downQueue.top().getDest() == currentFloor) {
			clk.advanceTime(1);
			int x = clk.getTime() - exitPerson().getTime();
			++totalPass;
			totalWait += x;
			std::cout << "Person reached destination after wating for time: " << clk.getTime() - exitPerson().getTime() << std::endl;
		}
	}
}

// Determines if elevator should stop at current floor

bool Elevator::stopAtFloor() const
{
	// Don't stop if full
	if (isFull())
		return false;

	// Stop if there is someone whose destination is that floor
	if (isGoingUp) {
		if (!upQueue.empty() && upQueue.top().getDest() == currentFloor)
			return true;
	}
	else {
		if (!downQueue.empty() && downQueue.top().getDest() == currentFloor)
			return true;
	}

	// Stop if there are people on the floor waiting for elevator
	if (building->getFloor(currentFloor).getButton().isActive())
		return true;

	return false;
}

// Calculate avg wait time

float Elevator::getAvgWait() const
{
	return float(totalWait)/float(totalPass);
}

int Elevator::numServed() const
{
	return totalPass;
}

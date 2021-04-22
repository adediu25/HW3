#include "Floor.h"

Floor::Floor(int num)
{
	floorNum = num;
	button = Button();
}

int Floor::getFloorNum() const
{
	return floorNum;
}

Button& Floor::getButton()
{
	return button;
}

void Floor::addPerson(const Person& person)
{
	elevatorQueue.push(person);
	if (person.getDest() - person.getFloor() > 0)
		button.pressDown();
	else
		button.pressUp();
}

Person Floor::removePerson()
{
	Person ret = Person(elevatorQueue.front().getDest(), elevatorQueue.front().getFloor());
	elevatorQueue.pop();
	if (elevatorQueue.empty())
		button.reset();
	return ret;
}

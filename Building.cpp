#include "Building.h"

Building::Building(std::string name, std::vector<Floor> flrs)
{
	buildingName = name;
	floors = flrs;
	bottomFlr = floors[0].getFloorNum();
	topFlr = floors.back().getFloorNum();
}

std::string Building::getName() const
{
	return buildingName;
}

Floor& Building::getFloor(int flr)
{
	int f = flr - floors[0].getFloorNum();
	return floors[f];
}

int Building::getTop() const
{
	return topFlr;
}

int Building::getBottom() const
{
	return bottomFlr;
}

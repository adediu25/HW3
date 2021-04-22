#pragma once
#include <vector>
#include <string>
#include "Floor.h"

class Building {
private:
	std::string buildingName;
	std::vector<Floor> floors;
	int topFlr;
	int bottomFlr;
public:
	Building() = default;
	Building(std::string, std::vector<Floor>);
	std::string getName() const;
	Floor& getFloor(int);
	int getTop() const;
	int getBottom() const;
};
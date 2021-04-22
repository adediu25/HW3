#pragma once

class Person {
private:
	int destFloor;
	int currFloor;
public:
	Person(int, int);
	Person();
	int getDest() const;
	int getFloor() const;
	bool operator>(const Person&) const;
	bool operator<(const Person&) const;
};
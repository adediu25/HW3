#pragma once

class Person {
private:
	int destFloor;
	int currFloor;
	int startTime;
public:
	Person(int, int);
	Person();
	void setFloor(int);
	int getDest() const;
	int getFloor() const;
	int getTime() const;
	bool operator>(const Person&) const;
	bool operator<(const Person&) const;
};
#include "Clock.h"

Clock::Clock()
{
	time = 0;
}

int Clock::getTime() const
{
	return time;
}

void Clock::advanceTime(int advTime)
{
	time += advTime;
}
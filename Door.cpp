#include "Door.h"
#include "GlobalClock.h"

Door::Door()
{
	doorAjar = false;
}

void Door::closeDoor()
{
	doorAjar = false;
	clk.advanceTime(1);
}

void Door::openDoor()
{
	doorAjar = true;
	clk.advanceTime(1);
}

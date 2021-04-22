#include "Door.h"

Door::Door()
{
	doorAjar = false;
}

void Door::closeDoor()
{
	doorAjar = false;
}

void Door::openDoor()
{
	doorAjar = true;
}

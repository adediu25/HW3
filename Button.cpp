#include "Button.h"

Button::Button()
{
	upBut = false;
	downBut = false;
}

bool Button::isActive() const
{
	if (upBut || downBut)
		return true;
	return false;
}

void Button::pressUp()
{
	upBut = true;
}

void Button::pressDown()
{
	downBut = true;
}

void Button::reset()
{
	upBut = false;
	downBut = false;
}

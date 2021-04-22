#pragma once

class Button {
private:
	bool upBut;
	bool downBut;
public:
	Button();
	bool isActive() const;
	void pressUp();
	void pressDown();
	void reset();
};
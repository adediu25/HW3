#pragma once

class Clock {
private:
	int time;
public:
	Clock();
	int getTime() const;
	void advanceTime(int);
};

extern Clock clk;
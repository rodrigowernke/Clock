#pragma once

#include "Arduino.h"

class Display {
public:
	Display();
	void DisplayTime(int hour, int minutes);
private:
	void DrawNumber(int number, int displayId);
	void DisplayHour(int hour);
	void DisplayMinutes(int min);
private:
	unsigned int D1 = 9;
	unsigned int D2 = 8;
	unsigned int D3 = 7;
	unsigned int D4 = 6;
	unsigned int A = A1;
	unsigned int B = 3;
	unsigned int C = 2;
	unsigned int D = A0;
	unsigned int DELAY = 1;
};
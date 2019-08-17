#include "Display.h"
#include "Timer.h"

Display::Display()
{
	pinMode(D1, OUTPUT);
	pinMode(D2, OUTPUT);
	pinMode(D3, OUTPUT);
	pinMode(D4, OUTPUT);
	pinMode(A, OUTPUT);
	pinMode(B, OUTPUT);
	pinMode(C, OUTPUT);
	pinMode(D, OUTPUT);
}

void Display::DisplayTime(int hour, int minutes)
{
	DisplayHour(hour);
	Timer::Delay(DELAY);
	DisplayMinutes(minutes);
	Timer::Delay(DELAY);
}

void Display::DisplayHour(int hour)
{
	unsigned int digits[2] = { 0, 0 };

	unsigned int counter = 0;

	while (hour > 0)
	{
		int digit = hour % 10;
		hour /= 10;

		digits[counter] = digit;
		counter++;
	}

	DrawNumber(digits[1], D1);
	Timer::Delay(DELAY);
	DrawNumber(digits[0], D2);
}

void Display::DisplayMinutes(int min)
{
	unsigned int digits[2] = { 0, 0 };

	unsigned int counter = 0;

	while (min > 0)
	{
		int digit = min % 10;
		min /= 10;

		digits[counter] = digit;
		counter++;
	}

	DrawNumber(digits[1], D3);
	Timer::Delay(DELAY);
	DrawNumber(digits[0], D4);
}

void Display::DrawNumber(int number, int displayId)
{
	digitalWrite(D1, LOW);
	digitalWrite(D2, LOW);
	digitalWrite(D3, LOW);
	digitalWrite(D4, LOW);
	digitalWrite(A, LOW);
	digitalWrite(B, LOW);
	digitalWrite(C, LOW);
	digitalWrite(D, LOW);

	switch (number)
	{
	case 0:
		digitalWrite(displayId, HIGH);
		break;
	case 1:
		digitalWrite(displayId, HIGH);
		digitalWrite(A, HIGH);
		break;
	case 2:
		digitalWrite(displayId, HIGH);
		digitalWrite(B, HIGH);
		break;
	case 3:
		digitalWrite(displayId, HIGH);
		digitalWrite(A, HIGH);
		digitalWrite(B, HIGH);
		break;
	case 4:
		digitalWrite(displayId, HIGH);
		digitalWrite(C, HIGH);
		break;
	case 5:
		digitalWrite(displayId, HIGH);
		digitalWrite(A, HIGH);
		digitalWrite(C, HIGH);
		break;
	case 6:
		digitalWrite(displayId, HIGH);
		digitalWrite(B, HIGH);
		digitalWrite(C, HIGH);
		break;
	case 7:
		digitalWrite(displayId, HIGH);
		digitalWrite(A, HIGH);
		digitalWrite(B, HIGH);
		digitalWrite(C, HIGH);
		break;
	case 8:
		digitalWrite(displayId, HIGH);
		digitalWrite(D, HIGH);
		break;
	case 9:
		digitalWrite(displayId, HIGH);
		digitalWrite(A, HIGH);
		digitalWrite(D, HIGH);
		break;
	}
}
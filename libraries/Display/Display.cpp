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
	Timer::DelayMicros(DELAY);
	DisplayMinutes(minutes);
	//Timer::DelayMicros(DELAY);
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
	Timer::DelayMicros(DELAY);
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
	Timer::DelayMicros(DELAY);
	DrawNumber(digits[0], D4);
	Timer::DelayMicros(DELAY);
}

void Display::DrawNumber(int number, int displayId)
{
	PORTB = PORTB & B00000000;
	PORTC = PORTC & B00000000;
	PORTD = PORTD & B00000000;

	switch (number)
	{
	case 0:
		if (displayId == D1)
		{
			PORTB = PORTB | B00000010;
		}
		else if (displayId == D2)
		{
			PORTB = PORTB | B00000001;
		}
		else if (displayId == D3)
		{
			PORTD = PORTD | B10000000;
		}
		else if (displayId == D4)
		{
			PORTD = PORTD | B01000000;
		}
		break;
	case 1:
		if (displayId == D1)
		{
			PORTB = PORTB | B00000010;
			PORTC = PORTC | B00000010;
		}
		else if (displayId == D2)
		{
			PORTB = PORTB | B00000001;
			PORTC = PORTC | B00000010;
		}
		else if (displayId == D3)
		{
			PORTD = PORTD | B10000000;
			PORTC = PORTC | B00000010;
		}
		else if (displayId == D4)
		{
			PORTD = PORTD | B01000000;
			PORTC = PORTC | B00000010;
		}
		break;
	case 2:
		if (displayId == D1)
		{
			PORTB = PORTB | B00000010;
			PORTD = PORTD | B00001000;
		}
		else if (displayId == D2)
		{
			PORTB = PORTB | B00000001;
			PORTD = PORTD | B00001000;
		}
		else if (displayId == D3)
		{
			PORTD = PORTD | B10000000;
			PORTD = PORTD | B00001000;
		}
		else if (displayId == D4)
		{
			PORTD = PORTD | B01000000;
			PORTD = PORTD | B00001000;
		}
		break;
	case 3:
		if (displayId == D1)
		{
			PORTB = PORTB | B00000010;
			PORTD = PORTD | B00001000;
			PORTC = PORTC | B00000010;
		}
		else if (displayId == D2)
		{
			PORTB = PORTB | B00000001;
			PORTD = PORTD | B00001000;
			PORTC = PORTC | B00000010;
		}
		else if (displayId == D3)
		{
			PORTD = PORTD | B10000000;
			PORTD = PORTD | B00001000;
			PORTC = PORTC | B00000010;
		}
		else if (displayId == D4)
		{
			PORTD = PORTD | B01000000;
			PORTD = PORTD | B00001000;
			PORTC = PORTC | B00000010;
		}
		break;
	case 4:
		if (displayId == D1)
		{
			PORTB = PORTB | B00000010;
			PORTD = PORTD | B00000100;
		}
		else if (displayId == D2)
		{
			PORTB = PORTB | B00000001;
			PORTD = PORTD | B00000100;
		}
		else if (displayId == D3)
		{
			PORTD = PORTD | B10000000;
			PORTD = PORTD | B00000100;
		}
		else if (displayId == D4)
		{
			PORTD = PORTD | B01000000;
			PORTD = PORTD | B00000100;
		}
		break;
	case 5:
		if (displayId == D1)
		{
			PORTB = PORTB | B00000010;
			PORTC = PORTC | B00000010;
			PORTD = PORTD | B00000100;
		}
		else if (displayId == D2)
		{
			PORTB = PORTB | B00000001;
			PORTC = PORTC | B00000010;
			PORTD = PORTD | B00000100;
		}
		else if (displayId == D3)
		{
			PORTD = PORTD | B10000000;
			PORTC = PORTC | B00000010;
			PORTD = PORTD | B00000100;
		}
		else if (displayId == D4)
		{
			PORTD = PORTD | B01000000;
			PORTC = PORTC | B00000010;
			PORTD = PORTD | B00000100;
		}
		break;
	case 6:
		if (displayId == D1)
		{
			PORTB = PORTB | B00000010;
			PORTD = PORTD | B00000100;
			PORTD = PORTD | B00001000;
		}
		else if (displayId == D2)
		{
			PORTB = PORTB | B00000001;
			PORTD = PORTD | B00000100;
			PORTD = PORTD | B00001000;
		}
		else if (displayId == D3)
		{
			PORTD = PORTD | B10000000;
			PORTD = PORTD | B00000100;
			PORTD = PORTD | B00001000;
		}
		else if (displayId == D4)
		{
			PORTD = PORTD | B01000000;
			PORTD = PORTD | B00000100;
			PORTD = PORTD | B00001000;
		}
		break;
	case 7:
		if (displayId == D1)
		{
			PORTB = PORTB | B00000010;
			PORTC = PORTC | B00000010;
			PORTD = PORTD | B00001000;
			PORTD = PORTD | B00000100;
		}
		else if (displayId == D2)
		{
			PORTB = PORTB | B00000001;
			PORTC = PORTC | B00000010;
			PORTD = PORTD | B00001000;
			PORTD = PORTD | B00000100;
		}
		else if (displayId == D3)
		{
			PORTD = PORTD | B10000000;
			PORTC = PORTC | B00000010;
			PORTD = PORTD | B00001000;
			PORTD = PORTD | B00000100;
		}
		else if (displayId == D4)
		{
			PORTD = PORTD | B01000000;
			PORTC = PORTC | B00000010;
			PORTD = PORTD | B00001000;
			PORTD = PORTD | B00000100;
		}
		break;
	case 8:
		if (displayId == D1)
		{
			PORTB = PORTB | B00000010;
			PORTC = PORTC | B00000001;
		}
		else if (displayId == D2)
		{
			PORTB = PORTB | B00000001;
			PORTC = PORTC | B00000001;
		}
		else if (displayId == D3)
		{
			PORTD = PORTD | B10000000;
			PORTC = PORTC | B00000001;
		}
		else if (displayId == D4)
		{
			PORTD = PORTD | B01000000;
			PORTC = PORTC | B00000001;
		}
		break;
	case 9:
		if (displayId == D1)
		{
			PORTB = PORTB | B00000010;
			PORTC = PORTC | B00000010;
			PORTC = PORTC | B00000001;
		}
		else if (displayId == D2)
		{
			PORTB = PORTB | B00000001;
			PORTC = PORTC | B00000010;
			PORTC = PORTC | B00000001;
		}
		else if (displayId == D3)
		{
			PORTD = PORTD | B10000000;
			PORTC = PORTC | B00000010;
			PORTC = PORTC | B00000001;
		}
		else if (displayId == D4)
		{
			PORTD = PORTD | B01000000;
			PORTC = PORTC | B00000010;
			PORTC = PORTC | B00000001;
		}
		break;
	}
}
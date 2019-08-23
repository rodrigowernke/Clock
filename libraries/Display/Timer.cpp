#include "Timer.h"
#include "Arduino.h"

static void Timer::DelayMillis(unsigned long milliseconds) {
	unsigned long currentMillis = millis();
	unsigned long previousMillis = currentMillis;

	while (currentMillis - previousMillis < milliseconds) {
		currentMillis = millis();
	}
}

static void Timer::DelayMicros(unsigned long microseconds)
{
	unsigned long currentMicros = micros();
	unsigned long previousMicros = currentMicros;

	while (currentMicros - previousMicros < microseconds)
	{
		currentMicros = micros();
	}
}
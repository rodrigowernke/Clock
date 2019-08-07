#include "Timer.h"
#include "Arduino.h"

static void Timer::Delay(long milliseconds) {
	unsigned long currentMillis = millis();
	unsigned long previousMillis = millis();

	while (currentMillis - previousMillis <= milliseconds) {
		currentMillis = millis();
	}
}
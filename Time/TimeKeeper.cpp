#include "TimeKeeper.h"
#include <Arduino.h>

TimeKeeper::TimeKeeper() : m_CurrentTime(0), m_Hour(0), m_Minute(0), m_Second(0) {

}

TimeKeeper::~TimeKeeper() {

}

unsigned int TimeKeeper::GetHour() {
	return m_Hour;
}

unsigned int TimeKeeper::GetMinute() {
	return m_Minute;
}

unsigned int TimeKeeper::GetSecond() {
	return m_Second;
}

void TimeKeeper::SyncTime(unsigned long time) {
	m_CurrentTime = time;
}

void TimeKeeper::Update() {
	while (millis() - m_PreviousMillis >= 1000) {
		m_PreviousMillis += 1000;

		m_CurrentTime++;

		m_Hour = (m_CurrentTime % 86400L) / 3600L;
		m_Minute = (m_CurrentTime % 3600L) / 60L;
		m_Second = m_CurrentTime % 60;
	}
}
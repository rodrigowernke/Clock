#include "TimeKeeper.h"
#include <Arduino.h>

TimeKeeper::TimeKeeper(unsigned long syncRateInMillis) : m_SyncRateInMillis(syncRateInMillis),
m_CurrentTime(0), m_Hour(0), m_Minute(0), m_Second(0), m_ReadyToUpdateTime(false), m_LeftOverMillis(0)
{
}

TimeKeeper::~TimeKeeper()
{

}

void TimeKeeper::Initialize(unsigned long updatedTime)
{
	m_CurrentTime = updatedTime;

	m_PreviousTimeMillis = millis();
}

unsigned int TimeKeeper::GetHour()
{
	return m_Hour;
}

unsigned int TimeKeeper::GetMinute()
{
	return m_Minute;
}

unsigned int TimeKeeper::GetSecond()
{
	return m_Second;
}

void TimeKeeper::SyncTime()
{
	if (m_ReadyToUpdateTime)
	{
		unsigned long updatedTime = m_SyncTimeFuncPtr();

		if (updatedTime != 0)
		{
			m_CurrentTime = updatedTime;

			m_ReadyToUpdateTime = false;
			m_PreviousSyncMillis = millis();
			m_PreviousTimeMillis = millis();
		}
	}
	else if (millis() - m_PreviousSyncMillis >= m_SyncRateInMillis)
	{
		// Update time with NTP server.
		// If m_SyncTimeFuncPtr returns 0 we can't use 
		// that time and we have to ask for it again in the next update.
		// while update time is not set, we keep track of time ourselves.

		unsigned long updatedTime = m_SyncTimeFuncPtr();

		if (updatedTime != 0)
		{
			m_CurrentTime = updatedTime;

			m_ReadyToUpdateTime = false;
			m_PreviousTimeMillis = millis();
			m_PreviousSyncMillis = millis();
		}
		else
		{
			m_ReadyToUpdateTime = true;
		}
	}
}

void TimeKeeper::SyncTimeFuncPtr(unsigned long(*Func)())
{
	m_SyncTimeFuncPtr = Func;
}

void TimeKeeper::Update()
{
	SyncTime();
	UpdateLocalTime();
}

void TimeKeeper::UpdateLocalTime()
{
	unsigned long timeSinceLastUpdate = millis() - m_PreviousTimeMillis;

	// At least one second has passed since last update.
	if (timeSinceLastUpdate >= 1000UL)
	{
		m_LeftOverMillis += timeSinceLastUpdate - 1000UL;

		m_PreviousTimeMillis += timeSinceLastUpdate;

		unsigned long addedTime = (timeSinceLastUpdate) / 1000UL;

		// time in seconds since 1970
		m_CurrentTime += addedTime;

		if (m_LeftOverMillis >= 1000UL)
		{
			m_LeftOverMillis = m_LeftOverMillis - 1000UL;
			m_CurrentTime += 1;
		}

		m_Hour = (m_CurrentTime % 86400UL) / 3600UL;
		m_Minute = (m_CurrentTime % 3600UL) / 60UL;
		m_Second = m_CurrentTime % 60UL;

		if (m_Hour < 10)
		{
			Serial.print("0");
			Serial.print(m_Hour);
		}
		else
		{
			Serial.print(m_Hour);
		}
		Serial.print(":");
		if (m_Minute < 10)
		{
			Serial.print("0");
			Serial.print(m_Minute);
		}
		else
		{
			Serial.print(m_Minute);
		}
		Serial.print(":");
		if (m_Second < 10)
		{
			Serial.print("0");
			Serial.print(m_Second);
		}
		else
		{
			Serial.print(m_Second);
		}
		Serial.print(" TK.");
		Serial.println("");
	}
}
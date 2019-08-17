#pragma once

#include "Display.h"

class TimeKeeper {
public:
	TimeKeeper(unsigned long syncRateInMillis);
	~TimeKeeper();

	void Update();
	void Initialize(unsigned long updatedTime);
	void SyncTimeFuncPtr(unsigned long(*Func)());

	unsigned int GetHour();
	unsigned int GetMinute();
	unsigned int GetSecond();
private:
	void UpdateLocalTime();
	void SyncTime();
private:
	Display m_Display;

	unsigned int m_Hour;
	unsigned int m_Minute;
	unsigned int m_Second;
	unsigned long m_CurrentTime;

	unsigned long (*m_SyncTimeFuncPtr)();
	// sync timer
	unsigned long m_SyncRateInMillis;
	unsigned long m_PreviousSyncMillis;

	// low level stuff
	unsigned long m_PreviousTimeMillis;


	//control time update if internet is off
	bool m_ReadyToUpdateTime;


	//test
	unsigned long m_LeftOverMillis;
};
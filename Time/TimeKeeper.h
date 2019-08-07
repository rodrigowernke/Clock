#pragma once

class TimeKeeper {
public:
	TimeKeeper();
	~TimeKeeper();

	unsigned int GetHour();
	unsigned int GetMinute();
	unsigned int GetSecond();
	void Update();
	void SyncTime(unsigned long time);
private:
	unsigned int m_Hour;
	unsigned int m_Minute;
	unsigned int m_Second;
	unsigned long m_CurrentTime;

	// low level stuff
	unsigned long m_PreviousMillis;
};
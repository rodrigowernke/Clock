#pragma once

#include "Arduino.h"
#include <EthernetUdp.h>

class NTPClient {
public:
	NTPClient();
	~NTPClient();

	void Initialize();
	void Update();

	int GetHour();
	int GetMinute();
	unsigned long GetNTPTime();
private:
	void SendNTPpacket(IPAddress& address);
	void FirstUpdate();
	void UpdateTime();
private:
	byte m_MacAddress[6] = { 0x00, 0x00, 0xAA, 0xBB, 0xCC, 0xDD };
	unsigned int m_LocalPort;
	const int NTP_PACKET_SIZE = 48;
	byte m_PacketBuffer[48];

	int m_Minute;
	int m_Hour;
	int m_UpdateDelay;
	unsigned long time_now = 0;

	EthernetUDP m_EthernetUDP;
	IPAddress m_TimeServerA;
	IPAddress m_TimeServerB;
	IPAddress m_TimeServerC;
};
#pragma once

#include <Arduino.h>
#include <EthernetUdp.h>

class NTPClient {
public:
	NTPClient();
	~NTPClient();

	void Initialize();
	unsigned long InitializeTime();
	void Update();
	unsigned long GetNTPTime();
private:
	void SendNTPpacket(IPAddress& address);
	void PrintTimeFromServer(unsigned long time, const char* tittle);
private:
	// UDP package control things
	bool notEmptyPackage = false;
	bool previousPacketIsLoaded = false;
	
	byte m_MacAddress[6] = { 0x00, 0x00, 0xAA, 0xBB, 0xCC, 0xDD };
	byte m_IP[4] = { 192, 168, 17, 90 };
	unsigned int m_LocalPort;
	const int NTP_PACKET_SIZE = 48;
	byte m_PacketBuffer[48];
	
	EthernetUDP m_EthernetUDP;
	IPAddress m_TimeServerA;
	IPAddress m_TimeServerB;
	IPAddress m_TimeServerC;


	// request stuff
	unsigned long m_RequestRateInMillis;
	unsigned long m_PreviousRequest;
};
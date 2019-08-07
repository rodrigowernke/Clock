#include "NTPClient.h"
#include <Timer.h>

NTPClient::NTPClient() : m_LocalPort(80), m_TimeServerA(200, 160, 0, 8), m_Hour(0), m_Minute(0), m_UpdateDelay(10000) {
}

void NTPClient::Initialize() {

	bool connected = false;

	while (!connected) {
		if (Ethernet.begin(m_MacAddress) == 0) {
			Serial.println("Failed to configure Ethernet using DHCP.");
		}
		else {
			connected = true;
			Serial.println("Connected.");
		}
	}

	m_EthernetUDP.begin(m_LocalPort);
}

NTPClient::~NTPClient() {

}

void NTPClient::FirstUpdate() {
	SendNTPpacket(m_TimeServerA);

	while (!m_EthernetUDP.parsePacket());
	// We've received a packet, read the data from it
	m_EthernetUDP.read(m_PacketBuffer, NTP_PACKET_SIZE); // read the packet into the buffer

	// the timestamp starts at byte 40 of the received packet and is four bytes,
	// or two words, long. First, esxtract the two words:

	unsigned long highWord = word(m_PacketBuffer[40], m_PacketBuffer[41]);
	unsigned long lowWord = word(m_PacketBuffer[42], m_PacketBuffer[43]);
	// combine the four bytes (two words) into a long integer
	// this is NTP time (seconds since Jan 1 1900):
	unsigned long secsSince1900 = highWord << 16 | lowWord;
	const unsigned long seventyYears = 2208988800UL;
	// subtract seventy years:
	unsigned long epoch = secsSince1900 - seventyYears;

	m_Hour = (epoch % 86400L) / 3600;

	switch (m_Hour)
	{
	case 0:
		m_Hour = 21;
		break;
	case 1:
		m_Hour = 22;
		break;
	case 2:
		m_Hour = 23;
		break;
	case 3:
		m_Hour = 0;
		break;
	case 4:
		m_Hour = 1;
		break;
	case 5:
		m_Hour = 2;
		break;
	case 6:
		m_Hour = 3;
		break;
	case 7:
		m_Hour = 4;
		break;
	case 8:
		m_Hour = 5;
		break;
	case 9:
		m_Hour = 6;
		break;
	case 10:
		m_Hour = 7;
		break;
	case 11:
		m_Hour = 8;
		break;
	case 12:
		m_Hour = 9;
		break;
	case 13:
		m_Hour = 10;
		break;
	case 14:
		m_Hour = 11;
		break;
	case 15:
		m_Hour = 12;
		break;
	case 16:
		m_Hour = 13;
		break;
	case 17:
		m_Hour = 14;
		break;
	case 18:
		m_Hour = 15;
		break;
	case 19:
		m_Hour = 16;
		break;
	case 20:
		m_Hour = 17;
	case 21:
		m_Hour = 18;
		break;
	case 22:
		m_Hour = 19;
		break;
	case 23:
		m_Hour = 20;
		break;
	}

	m_Minute = (epoch % 3600) / 60;
}

void NTPClient::Update() {
	if (millis() > time_now + m_UpdateDelay) {
		time_now = millis();

		UpdateTime();
	}
}

int NTPClient::GetHour() {
	return m_Hour;
}

int NTPClient::GetMinute() {
	return m_Minute;
}

void NTPClient::UpdateTime() {

	SendNTPpacket(m_TimeServerA);

	//while (!m_EthernetUDP.parsePacket());
	if (m_EthernetUDP.parsePacket())
	{

		// We've received a packet, read the data from it
		m_EthernetUDP.read(m_PacketBuffer, NTP_PACKET_SIZE); // read the packet into the buffer

		//the timestamp starts at byte 40 of the received packet and is four bytes,
		// or two words, long. First, esxtract the two words:

		unsigned long highWord = word(m_PacketBuffer[40], m_PacketBuffer[41]);
		unsigned long lowWord = word(m_PacketBuffer[42], m_PacketBuffer[43]);
		// combine the four bytes (two words) into a long integer
		// this is NTP time (seconds since Jan 1 1900):
		unsigned long secsSince1900 = highWord << 16 | lowWord;
		const unsigned long seventyYears = 2208988800UL;
		// subtract seventy years:
		unsigned long epoch = secsSince1900 - seventyYears;

		m_Hour = (epoch % 86400L) / 3600;

		switch (m_Hour)
		{
		case 0:
			m_Hour = 21;
			break;
		case 1:
			m_Hour = 22;
			break;
		case 2:
			m_Hour = 23;
			break;
		case 3:
			m_Hour = 0;
			break;
		case 4:
			m_Hour = 1;
			break;
		case 5:
			m_Hour = 2;
			break;
		case 6:
			m_Hour = 3;
			break;
		case 7:
			m_Hour = 4;
			break;
		case 8:
			m_Hour = 5;
			break;
		case 9:
			m_Hour = 6;
			break;
		case 10:
			m_Hour = 7;
			break;
		case 11:
			m_Hour = 8;
			break;
		case 12:
			m_Hour = 9;
			break;
		case 13:
			m_Hour = 10;
			break;
		case 14:
			m_Hour = 11;
			break;
		case 15:
			m_Hour = 12;
			break;
		case 16:
			m_Hour = 13;
			break;
		case 17:
			m_Hour = 14;
			break;
		case 18:
			m_Hour = 15;
			break;
		case 19:
			m_Hour = 16;
			break;
		case 20:
			m_Hour = 17;
		case 21:
			m_Hour = 18;
			break;
		case 22:
			m_Hour = 19;
			break;
		case 23:
			m_Hour = 20;
			break;
		}

		m_Minute = (epoch % 3600) / 60;
	}
}

unsigned long NTPClient::GetNTPTime() {

	SendNTPpacket(m_TimeServerA);

	while (!m_EthernetUDP.parsePacket());
	// We've received a packet, read the data from it
	m_EthernetUDP.read(m_PacketBuffer, NTP_PACKET_SIZE); // read the packet into the buffer

	//the timestamp starts at byte 40 of the received packet and is four bytes,
	// or two words, long. First, esxtract the two words:

	unsigned long highWord = word(m_PacketBuffer[40], m_PacketBuffer[41]);
	unsigned long lowWord = word(m_PacketBuffer[42], m_PacketBuffer[43]);
	// combine the four bytes (two words) into a long integer
	// this is NTP time (seconds since Jan 1 1900):
	unsigned long secsSince1900 = highWord << 16 | lowWord;
	const unsigned long seventyYears = 2208988800UL;
	// subtract seventy years:
	return secsSince1900 - seventyYears - 3 * 3600;
}

void NTPClient::SendNTPpacket(IPAddress& address) {
	// set all bytes in the buffer to 0
	memset(m_PacketBuffer, 0, NTP_PACKET_SIZE);
	// Initialize values needed to form NTP request
	// (see URL above for details on the packets)
	m_PacketBuffer[0] = 0b11100011;   // LI, Version, Mode
	m_PacketBuffer[1] = 0;     // Stratum, or type of clock
	m_PacketBuffer[2] = 6;     // Polling Interval
	m_PacketBuffer[3] = 0xEC;  // Peer Clock Precision
	// 8 bytes of zero for Root Delay & Root Dispersion
	m_PacketBuffer[12] = 49;
	m_PacketBuffer[13] = 0x4E;
	m_PacketBuffer[14] = 49;
	m_PacketBuffer[15] = 52;

	// all NTP fields have been given values, now
	// you can send a packet requesting a timestamp:

	m_EthernetUDP.beginPacket(address, 123); //NTP requests are to port 123
	m_EthernetUDP.write(m_PacketBuffer, NTP_PACKET_SIZE);
	m_EthernetUDP.endPacket();
}
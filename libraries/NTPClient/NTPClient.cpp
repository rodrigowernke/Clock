#include "NTPClient.h"

NTPClient::NTPClient() : m_LocalPort(80), m_TimeServerA(200, 160, 0, 8), m_RequestRateInMillis(5000), m_PreviousRequest(0)
{
}

void NTPClient::Initialize()
{
	bool connected = false;

	while (!connected)
	{
		if (Ethernet.begin(m_MacAddress) == 0)
		{
			//Serial.println("Failed to configure Ethernet using DHCP.");
		}
		else
		{
			connected = true;
		}
	}

	m_EthernetUDP.begin(m_LocalPort);
}

NTPClient::~NTPClient()
{

}

// Gets the updated time from a NTP server.
// Timezone is set to UTC -3:00. 
unsigned long NTPClient::GetNTPTime()
{
	unsigned long start = millis();

	while (true)
	{
		SendNTPpacket(m_TimeServerA);

		notEmptyPackage = (m_EthernetUDP.parsePacket() > 0);

		// Raise flag that a packet is loaded and read it in the buffer
		if (notEmptyPackage)
		{
			m_EthernetUDP.read(m_PacketBuffer, NTP_PACKET_SIZE);
			previousPacketIsLoaded = true;

		}
		// If the current packet is empty, but a loaded packet exists, break out of the loop
		else if (!notEmptyPackage && previousPacketIsLoaded)
		{
			previousPacketIsLoaded = false;
			break;
		}

		if (millis() - start > 5)
		{
			return 0;
		}
	}

	unsigned long end = millis();

	unsigned long timer = end - start;

	notEmptyPackage = false;
	previousPacketIsLoaded = false;

	//the timestamp starts at byte 40 of the received packet and is four bytes,
	// or two words, long. First, esxtract the two words:

	unsigned long highWord = word(m_PacketBuffer[40], m_PacketBuffer[41]);
	unsigned long lowWord = word(m_PacketBuffer[42], m_PacketBuffer[43]);
	// combine the four bytes (two words) into a long integer
	// this is NTP time (seconds since Jan 1 1900):
	unsigned long secsSince1900 = highWord << 16 | lowWord;
	const unsigned long seventyYears = 2208988800UL;
	// subtract seventy years:

	//UTC -3:00
	int timezone = -3;

	unsigned long updatedTime = secsSince1900 - seventyYears + timezone * 3600;

	PrintTimeFromServer(updatedTime, "UT");

	return updatedTime;
}

unsigned long NTPClient::InitializeTime()
{
	while (true)
	{
		SendNTPpacket(m_TimeServerA);

		notEmptyPackage = (m_EthernetUDP.parsePacket() > 0);

		if (notEmptyPackage)
		{
			// raise flag that a packet is loaded and read it in the buffer
			m_EthernetUDP.read(m_PacketBuffer, NTP_PACKET_SIZE);
			previousPacketIsLoaded = true;
		}
		else if (!notEmptyPackage && previousPacketIsLoaded)
		{
			// if the current packet is empty, but a loaded packet exists, break out of the loop
			previousPacketIsLoaded = false;
			//Serial.println("Achou o pacote correto");
			//Serial.println("Loaded package.");
			break;
		}
	}

	notEmptyPackage = false;
	previousPacketIsLoaded = false;

	//the timestamp starts at byte 40 of the received packet and is four bytes,
	// or two words, long. First, esxtract the two words:

	unsigned long highWord = word(m_PacketBuffer[40], m_PacketBuffer[41]);
	unsigned long lowWord = word(m_PacketBuffer[42], m_PacketBuffer[43]);
	// combine the four bytes (two words) into a long integer
	// this is NTP time (seconds since Jan 1 1900):
	unsigned long secsSince1900 = highWord << 16 | lowWord;
	const unsigned long seventyYears = 2208988800UL;
	// subtract seventy years:

	//UTC -3:00
	int timezone = -3;

	unsigned long updatedTime = secsSince1900 - seventyYears + timezone * 3600;

	PrintTimeFromServer(updatedTime, "IT");

	return updatedTime;
}

void NTPClient::Update()
{
	int result = Ethernet.maintain();

	if (result != 0)
	{
		//Serial.print("Ethernet.maintain(): ");
		//Serial.println(result);
	}
}

void NTPClient::SendNTPpacket(IPAddress& address)
{
	if (millis() - m_PreviousRequest < m_RequestRateInMillis)
	{
		return;
	}

	// Update previous request tracker.
	m_PreviousRequest = millis();

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

	//Serial.println("Requested time from NTP server.");
}

void NTPClient::PrintTimeFromServer(unsigned long updatedTime, const char* tittle)
{
	unsigned long hour = (updatedTime % 86400L) / 3600L;
	unsigned long minute = (updatedTime % 3600L) / 60L;
	unsigned long second = updatedTime % 60;

	if (hour < 10)
	{
		Serial.print("0");
		Serial.print(hour);
	}
	else
	{
		Serial.print(hour);
	}
	Serial.print(":");
	if (minute < 10)
	{
		Serial.print("0");
		Serial.print(minute);
	}
	else
	{
		Serial.print(minute);

	}
	Serial.print(":");
	if (second < 10)
	{
		Serial.print("0");
		Serial.print(second);
	}
	else
	{
		Serial.print(second);
	}
	Serial.print(" ");
	Serial.print(tittle);
	Serial.print(".");
	Serial.println("");
}
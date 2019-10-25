#include <Display.h>
#include <NTPClient.h>
#include <TimeKeeper.h>

Display display;
NTPClient ntpClient;
TimeKeeper timeKeeper(3600000UL * 4);

void setup() {
  Serial.begin(9600);
  while (!Serial);

  ntpClient.Initialize();
  timeKeeper.Initialize(ntpClient.InitializeTime());
  timeKeeper.SyncTimeFuncPtr(GetNTPTime);
}

void loop() {
  ntpClient.Update();
  timeKeeper.Update();
  display.DisplayTime(timeKeeper.GetHour(), timeKeeper.GetMinute());
}

unsigned long GetNTPTime() {
  return ntpClient.GetNTPTime();
}

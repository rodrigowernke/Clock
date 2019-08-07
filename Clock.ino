#include <Display.h>
#include <NTPClient.h>
#include <TimeKeeper.h>

Display display;
NTPClient ntpClient;
TimeKeeper timeKeeper;
////////////////////////////////////////////////

unsigned long timer = 1000;
unsigned long current = 0;

////////////////////////////////////////////////

void setup() {
  Serial.begin(9600);
  while (!Serial);

  ntpClient.Initialize();
  timeKeeper.SyncTime(ntpClient.GetNTPTime());
}

void loop() {
  timeKeeper.Update();
  display.DisplayTime(timeKeeper.GetHour(), timeKeeper.GetMinute());
  
  if (millis() > current + timer) {
    current = millis();
    
    Serial.print(timeKeeper.GetHour());
    Serial.print(":");
    Serial.print(timeKeeper.GetMinute());
    Serial.print(":");
    Serial.print(timeKeeper.GetSecond());
    Serial.println("");
  }
}

#include <Display.h>

Display display;

void setup() {
  Serial.begin(9600);
  while(!Serial);
}

void loop() {
  display.DisplayTime(18, 53);
}

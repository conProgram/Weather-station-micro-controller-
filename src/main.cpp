#include <Arduino.h>
#include <serverClass.cpp>

void setup() {
  Serial.begin(115200); // opens serial port, sets data rate to bps
	Serial.println("Serial port open");
  bigSetUpMethod();
  Serial.println("Ouputs set to 5 Seconds by default press outputbutton to change the output time");
  delay(2000);
}

void loop() {
 bigLoopMethod();
}
#include <Arduino.h>
#include <sdCard.cpp>
void setup() {
  Serial.begin(115200); // opens serial port, sets data rate to bps
	Serial.println("Serial port open");
  Serial.println("Ouputs set to 5 Seconds by default press outputbutton to change the output time");
  //Set up methods have been passed here
  setUpPassing();
  SDcardsetup();
  delay(2000);
}

//All looping methods are passed here from sdCard class
void loop() {
 loopPassing();
}
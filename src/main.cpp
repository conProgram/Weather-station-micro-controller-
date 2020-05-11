#include <Arduino.h>
#include <sdCard.cpp>

//All methods used to set up the componets are passed into this loop
void setup() {
  Serial.begin(115200); // opens serial port to be used, sets data rate to bps
	Serial.println("Serial port open");
  Serial.println("Ouputs set to 5 Seconds by default press outputbutton to change the output time");
  
  //Set up methods have been passed here
  setUpPassing();
  SDcardsetup();
  
  delay(2000); //Small delay to allow sensors componets to be completely set up before the program continues in testing we found this to work the best
}

//All looping methods are passed here from sdCard class
void loop() {
 twoMinsSDCardWrite();
 //LoopPassing holds all the looping methods in the system. 
 loopPassing();
}


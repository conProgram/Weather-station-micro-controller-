#include <Arduino.h>
#include <rgbColorSet.cpp>
#include <consoleOutputTime.cpp>


//Pir Sensor Button
//const int PushButton = 27;

//Pin for PIR sensor
const int pirPin = 27;

//Pir Status
int pirStatus = 0;

int currentTime;
int tenMinsTime;

//Used for the state of the PIR sensor button
//int Push_button_state = 0;

//Counts PIR sensor activation
int buttonPresses = 0;

long previousMillis = 0;
int interval = 5000;

void setup() {
  Serial.begin(115200); // opens serial port, sets data rate to bps
	Serial.println("Serial port open");
  dhtClassSetupCalling();
  humiditySetUpClass();
  tempratureSetupClass();
  outputButtonSetup();
  alarmClassSetupCalling();
  

  pinMode(pirPin, INPUT);
  Serial.println("Waiting on PIR sensor ...");
  
}

void loop() {
 
 interval = outputButton();
 
 //Push_button_state = digitalRead(PushButton);
  pirStatus = digitalRead(pirPin);
 	
   //Due to my PIR Sensor not working I have had to set the state to on for testing purposes 
   pirStatus = HIGH;
   //High is activated
	 if (pirStatus == HIGH) {
     //Easier to understand for me than ++ as dont want the PIR sensor spamming the counter 
 		buttonPresses = 1;
    currentTime = millis();
    tenMinsTime = millis() + 600000;
    delay(1000);// Debounce
 	  Serial.println("PIR SENSOR IS ACTIVATED");
    Serial.println("10 min timer activated");
	}

  while(currentTime <= tenMinsTime){
  switch (buttonPresses) {
	case 0:
	digitalWrite(greenHum, LOW);
	digitalWrite(blueHum, LOW);
	digitalWrite(redHum, LOW);
	digitalWrite(greenTemp, LOW);
	digitalWrite(blueTemp, LOW);
	digitalWrite(redTemp, LOW);
		break;

	case 1:
	break;

	case 2:
		Serial.println("system off...");
    buttonPresses = 0;
		break;
  
	default:
	Serial.print("switch case haven't run correctly");
	break;

	}

  while (buttonPresses == 1)
  {
    //Checks to see if the current time is less than the delay time that has been passes from the consoleOutputTime method 
   unsigned long currentMillis = millis();
  if(currentMillis - previousMillis > interval) {
      Serial.print("The temprature is: ");
      Serial.println(tempratureValue);
      Serial.print("The humiduty value is: ");
      Serial.println(humidtyValue);
      previousMillis = currentMillis;
      //Serial.print("Actual output time is = ");
      //Serial.println(interval);
}
  tempReturn();
  RGBTempClass();
  humReturn();
  alarmCalled();
  RGBHumClass();
  outputButtonRead();
  break;


  }
 
}
while(currentTime > tenMinsTime){
  Serial.println("10 Mins has passed");
  currentTime = millis();
  tenMinsTime = millis() + 600000;
  buttonPresses = 2;
  break;
}
}
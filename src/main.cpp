#include <Arduino.h>
#include <rgbColorSet.cpp>
#include <consoleOutputTime.cpp>
//Pir Sensor Button
const int PushButton = 27;
//Used for the state of the PIR sensor button
int Push_button_state = 0;
//Counts PIR sensors button presses
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
  Serial.println("Waiting on PIR sensor ...");
  
}

void loop() {
 
 
 interval = outputButton();

 Push_button_state = digitalRead(PushButton);

 	
	 if (Push_button_state == LOW) {
 		buttonPresses ++;
 		delay(1000);
 	//Serial.println("PIR SENSOR IS ACTIVATED");
	}

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
    
   unsigned long currentMillis = millis();
  if(currentMillis - previousMillis > interval) {
  Serial.println("Output time every 5 seconds");
      Serial.print("The temprature is: ");
      Serial.println(tempratureValue);
      Serial.print("The humiduty value is: ");
      Serial.println(humidtyValue);
      previousMillis = currentMillis;
}
  outputButtonRead();
  tempReturn();
  RGBTempClass();
  humReturn();
  RGBHumClass();
  
  
  break;


  }
 
}
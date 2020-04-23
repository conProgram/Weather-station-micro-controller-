#include <Arduino.h>
#include <rgbColorSet.cpp>
#include <consoleOutputTime.cpp>



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

//Checks to see if system is on or off
int systemState = 0;

//All setup methods that are below pirSensorClass are passed here to can be called in main loop
void setupPirClass() {
  //DHT11 set up 
  dhtClassSetupCalling();
  //Sets up humdiity RGB's
  humiditySetUpClass();
  //Sets up temprature RGB's
  tempratureSetupClass();
  //Sets up output time button
  outputButtonSetup();
  //Sets the alarm up
  alarmClassSetupCalling();
  //Passes the alarm to be activated/snoozed
  alarmCalled();
  //Sets PIR sesnsor input
  pinMode(pirPin, INPUT);
  Serial.println("Waiting on PIR sensor ...");
}


//This is the pir sensor class used for callign all the methods once the system is on
void loopingPirSensor() {
 
 //This is old code from when PIR sensor was just a push button left this so you can see improvment 
 //Push_button_state = digitalRead(PushButton); 

//Checks to see if PIR sensor has been activated or not
  pirStatus = digitalRead(pirPin);
 	
   //Due to my PIR Sensor not working I have had to set the state to HIGH to demonstrate it working
   pirStatus = HIGH;

   //High is activated
	 if (pirStatus == HIGH) {
     //setting button presses to 1 rather than useing ++ as dont want the PIR sensor spamming the counter 
 		buttonPresses = 1;
    //Gets current time
    currentTime = millis();
    //Works out 10 mins from now as deivce mus tturn itself off after 10 mins
    tenMinsTime = millis() + 600000;
    delay(1000);// Debounce
 	  Serial.println("PIR SENSOR IS ACTIVATED");
    Serial.println("10 min timer activated");
	}

  //Aslong as currrent time is less than 10 mins it will run the code 
  while(currentTime <= tenMinsTime){
  
  //Switch case is used to dertermin the state of the program, 0 is off 1 is on
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

//This use case is just a temporary state this is just for if the system turns off it tells the user
  	case 2:
		Serial.println("system off...");
    buttonPresses = 0;
		break;

//The default should never run unless there is an issue with something in the program
	default:
	Serial.print("switch case haven't run correctly");
	break;

	}
//If system is on buttonPresses is set to 1 and system runs in a while loop 
//All methods used in the program are called in this while loop
//buttonPresses is an inapporpiate name from when the pirSensor was just a button
  while (buttonPresses == 1)
  {
    interval = outputButton();
    //Checks to see if the current time is less than the delay time that has been passes from the consoleOutputTime method 
   unsigned long currentMillis = millis();

   //This loop checks the see what the output time is
   //Once the output time has passed it will then output the temprature and humidity values
  if(currentMillis - previousMillis > interval) {
      Serial.print("The temprature is: ");
      Serial.println(tempratureValue);
      Serial.print("The humiduty value is: ");
      Serial.println(humidtyValue);
      previousMillis = currentMillis;
      
      //This was used to ensure the output delay time was passed into this method correctly
      // Serial.print("Actual output time is = ");
      // Serial.println(interval);
}

//These are all the looping methods called from other classes 
  tempReturn();
  RGBTempClass();
  humReturn();
  alarmCalled();
  RGBHumClass();
  outputButtonRead();
  break;


  }
 
}

//Once 10 misn has passed it sets the switch case above to 2 which turns off the system ans resets it 
while(currentTime > tenMinsTime){
  Serial.println("10 Mins has passed");
  currentTime = millis();
  tenMinsTime = millis() + 600000;
  buttonPresses = 2;
  break;
}
}

//Due to the way C++ Works I need to pass the values from my rgbColor set to the server code 
//This is because DHT values can only be read in once by the system and therefore has to be passed around the program

int tempPassing(){
return tempratureValue; //passes the temprature value to serverCode.cpp
}
int humPassing(){
return humidtyValue; //passes the humidity value to serverCode.cpp
}
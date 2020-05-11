#include <Arduino.h>
#include <rgbColorSet.cpp>
#include <consoleOutputTime.cpp>

//Pin for PIR sensor
const int pirPin = 27;

//Pir Status off by default
int pirStatus = LOW;

//Used to time 10 mins since start of program
int currentTime;
int tenMinsTime = 600000;
int preLoop = 0;

//Counts PIR sensor activation
int buttonPresses = 0; //Button presses is used as this detrmin what stage the PIR sensor is at, this is changed by time rather than physical button presses

//Used for output time
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
  pirStatus = LOW;
  Serial.println("Waiting on PIR sensor ...");

}



void outputToConsole(){
    interval = outputButton(); //This is the delay value returned from the consoleOutputTimeClass
    int currentMillis = millis();

   //This loop checks the see what the output time is
   //Once the output time has passed it will then output the temprature and humidity values
    if(currentMillis - previousMillis > interval) {
      Serial.print("The temprature is: ");
      Serial.println(tempratureValue);
      Serial.print("The humiduty value is: ");
      Serial.println(humidtyValue);
      previousMillis = currentMillis;
      
      //This was used in debugging to ensure the output delay time was passed into this method correctly
      // Serial.print("Actual output time is = ");
      // Serial.println(interval);
      }
}


//If pir sensor detects movement it will turn the system on
void IRAM_ATTR detectsMovement() {
  buttonPresses = 1;
  systemState = 1;
}


void loopingPirSensor() {
 //This is old code from when PIR sensor was just a push button left this so you can see improvment 
 //Push_button_state = digitalRead(PushButton); 

    // Set motionSensor pin as interrupt, assign interrupt function and set RISING mode
    pinMode(pirPin, INPUT_PULLUP);
    attachInterrupt(digitalPinToInterrupt(pirPin), detectsMovement, RISING); // These two lines of code allow the user to restart the timer at any point by causing movement
    
    
    //Checks to see if PIR sensor has been activated or not
    pirStatus = digitalRead(pirPin);

  //This If statment also checks for PIR movement using a diffrent technique if the PIR sensor is high it turns the system on
	
   if (pirStatus == HIGH) {
     //setting button presses to 1 rather than useing ++ as dont want the PIR sensor spamming the counter 
 		buttonPresses = 1;
    systemState = 1;
	}

  //This is the code for the 10 min timer on the PIR sensor 
  int currentPirTime = millis();
  //Aslong as currrent time is less than 10 mins it will run the code 
  while(currentPirTime - previousMillis > tenMinsTime){
  previousMillis = currentPirTime;
  buttonPresses = 2;
  systemState = 0;
  break;
  }

  //Code will only run while the system is fully on
  while(systemState == 1){
  
  //Switch case is used to dertermin the state of the program, 0 is off 1 is on
  switch (buttonPresses) {
	case 0:
	digitalWrite(greenHum, LOW);
	digitalWrite(blueHum, LOW);
	digitalWrite(redHum, LOW);
	digitalWrite(greenTemp, LOW);
	digitalWrite(blueTemp, LOW);
	digitalWrite(redTemp, LOW);
  digitalWrite(pinBuz, 0);
	break;

	case 1:
    //These are all the looping methods called from other classes 
    tempReturn();
    RGBTempClass();
    humReturn();
    alarmCalled();
    RGBHumClass();
    outputButtonRead();
    outputToConsole();
    break; //End of case 1

    //This use case is just a temporary state this is just for if the system turns off and it tells the user
  	case 2:
		Serial.println("system off...");
    Serial.println("Activate the PIR sensor to restart the system");
    buttonPresses = 0;
		break;
	}
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


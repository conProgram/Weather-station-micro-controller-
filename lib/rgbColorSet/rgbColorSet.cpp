#include <Arduino.h>
#include <alarm.cpp>

void dhtClassSetupCalling(){
  dhtClassSetupCallingOG();
}

void alarmClassSetupCalling(){
	alarmSetup();
}
void alarmCalled(){
	tempValueCheck();
	humValueCheck();
	whichAlarm();
}

int switchCaseTemp;
int switchCaseHum;

//Global 
//int switchCaseTemp;

//Temp RGB
const int redTemp = 4;
const int greenTemp = 16;
const int blueTemp = 17;

 void tempratureSetupClass(){
	//Temprature RGB's
	pinMode(redTemp, OUTPUT);
	pinMode(blueTemp, OUTPUT);
	pinMode(greenTemp, OUTPUT);
    Serial.println("temprature RGB initialised");
	
}

int tempReturn(){
	
    float t = tempPass(); //Reads temprature stores value in "t"
    
    if (isnan(t)) {
		Serial.println("Failed to read Temprature from DHT sensor!");
		Serial.println("Ensure DHT is connected correctly");
		delay(1000);
	}

	else if (t > 17 && t < 24) { //This is for the Green LED values to show all is good
		switchCaseTemp = 1; //Calls first switch case lighting up the green LED

	}

	else if ((t > 15 && t < 18) || (t > 23 && t < 28)) { // This is the Amber LED Values

		switchCaseTemp = 2; //Calls second switch case lighting up the Amber LED

	}

	else { //If the temperature is out of the two bounds of both the Green and Amber LED the Red LED is called

		switchCaseTemp = 3; //Calls switch case three light up the Red LED

	}
	return switchCaseTemp;
	
  
}

int RGBTempClass(){
    switch (switchCaseTemp) {
	case 1: //If switchCaseTemp is set to 1 useing the if statment above 
		digitalWrite(greenTemp, HIGH);
		digitalWrite(blueTemp, LOW);
		digitalWrite(redTemp, LOW);
		TempColorTypeReturn = 3;
		break; //Green led lights up

	case 2:
		digitalWrite(greenTemp, HIGH);
		digitalWrite(blueTemp, LOW);
		digitalWrite(redTemp, HIGH);
		TempColorTypeReturn = 2;
		break; //Amber LED lights up

	case 3:
		digitalWrite(greenTemp, HIGH);
		digitalWrite(blueTemp, LOW);
		digitalWrite(redTemp, LOW);
		TempColorTypeReturn = 1;
		break; // Red LED lights up

		//The default is set if my previous code crashes it will become obvious as the RGB will go CYAN
	default:
		//Serial.println(" Temprature Loop if statements haven't run correctly");
		digitalWrite(greenTemp, HIGH);
		digitalWrite(blueTemp, HIGH);
		digitalWrite(redTemp, LOW);
		//Serial.println("FAILED !");
		//Serial.print("Switch Case value is: ");
		Serial.print(switchCaseTemp);
		break;
	}
	return TempColorTypeReturn;
	}

// ----------------------------------------------------------------------------------------- //
//Humidity RGB Code all comments from above apply exactly the same to humidity class
//Except instead of useign the temprature varible we now use the humidity 

//Humidity RGB
const int redHum = 27;
const int greenHum = 13;
const int blueHum = 25;

 void humiditySetUpClass(){
  
	//Humdity RGB's
	pinMode(redHum, OUTPUT);
	pinMode(blueHum, OUTPUT);
	pinMode(greenHum, OUTPUT);
    Serial.println("Humidity RGB initialised");
}

int humReturn(){

float h = humPass();

    if (isnan(h)) {
		Serial.println("Failed to read Humidity from DHT sensor!");
		Serial.println("Ensure DHT is connected correctly");
		delay(2000);
	}

	if (h >= 35 && h <= 60) {

		switchCaseHum = 1;

	}

	else if ((h >= 25 && h <= 34) || (h >= 60 && h <= 75)) {
		switchCaseHum = 2;

	}

	else {
		switchCaseHum = 3;
	}
    
    return switchCaseHum;
	
  
}

int RGBHumClass(){
    switch (switchCaseHum) {
	case 1:
		digitalWrite(greenHum, HIGH);
		digitalWrite(blueHum, LOW);
		digitalWrite(redHum, LOW);
		HumColorTypeReturn = 3;
		break;

	case 2:
		digitalWrite(greenHum, HIGH);
		digitalWrite(blueHum, LOW);
		digitalWrite(redHum, HIGH);
		HumColorTypeReturn =  2;
		break;

	case 3:
		digitalWrite(greenHum, LOW);
		digitalWrite(blueHum, LOW);
		digitalWrite(redHum, HIGH);
		HumColorTypeReturn = 3;
		break;

	default:
		Serial.print("Loop if statements haven't run correctly");
		digitalWrite(greenHum, HIGH);
		digitalWrite(blueHum, HIGH);
		digitalWrite(redHum, LOW);
		Serial.println("Failed !!!");
		break;

	}
	return HumColorTypeReturn;
}


#include <Arduino.h>
//Buzzer
const int pinBuz = 12;

//Timeing Varibles used in the buzzer method are declared here 
int thirtySeconds;
int currentBuzzerTime;
int fiveSeconds;

void alarmSetup(){
    
	pinMode(pinBuz, INPUT);
    Serial.println("Buzzer initialised");

}

//Method for the buzzer code
int alarm(){
    
    digitalWrite(pinBuz, 1);

	}
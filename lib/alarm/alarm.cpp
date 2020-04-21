#include <Arduino.h>
//Buzzer
const int pinBuz = 26;

//Button to snooze the alarm 
const int snoozeButton = 18;

//Used for the state of the output time button
int alarm_button_state = 0;

//Timeing Varibles used in the buzzer method are declared here 
int thirtySeconds;
int currentBuzzerTime;
int fiveSeconds;
int twoMins;
int currentSnoozeTime;

int switchCaseTemp2 = 1;
int switchCaseHum2 = 1;

void alarmSetup(){
pinMode(pinBuz, INPUT);
Serial.println("Buzzer initialised");

}

//Method for the buzzer code
void alarm(){
    //Alarm button read in
	alarm_button_state = digitalRead(snoozeButton);

    while(currentSnoozeTime < twoMins){
		digitalWrite(pinBuz, 0);
        twoMins = millis() + 120000;
        currentSnoozeTime = millis();		
	
	}
	//If alarm/snooze button is pressed proving the RGB's are not green
	if (alarm_button_state == LOW){
		
		if(switchCaseTemp2 > 1 || switchCaseHum2 > 1){
		twoMins = millis() + 120000;
		currentSnoozeTime = millis();
		
		}}
	
	//If Amber LED is on either temprature or humidity this is run
	else if(switchCaseTemp2 == 2 || switchCaseHum2 == 2){
		thirtySeconds = millis() + 30000; //Calcuates 30 seconds time from when the amber LED is on
		currentBuzzerTime = millis(); //Gets current time
		
		//Alarm goes for 30 seconds
		if(currentBuzzerTime < thirtySeconds){
		digitalWrite(pinBuz, 1);	

	}
		//After 30 seconds alarm turns off and timer is resrtarted
	else if(currentBuzzerTime >= thirtySeconds){
		digitalWrite(pinBuz, 0);
		thirtySeconds = millis() + 30000;
		currentBuzzerTime = millis(); //Gets current time
	}
	
	//If Red LED is on either temprature or humidity this is run
	else if(switchCaseTemp2 == 3 || switchCaseHum2 == 3){
		fiveSeconds = millis() + 5000;
		currentBuzzerTime = millis();
		
		if(currentBuzzerTime < fiveSeconds){
		digitalWrite(pinBuz, 1);
		
	}else if(currentBuzzerTime >= fiveSeconds){
		digitalWrite(pinBuz, 0);
		fiveSeconds = millis() + 5000;
		currentBuzzerTime = millis();
	}
	}}
    

	}
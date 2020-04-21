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

int switchCaseTemp;
int switchCaseHum;

void alarmSetup(){
pinMode(pinBuz, INPUT);
Serial.println("Buzzer initialised");

}

//Method for the buzzer code
void alarm(){
    //Alarm button read in
	alarm_button_state = digitalRead(snoozeButton);
	
	//If alarm/snooze button is pressed do this
	if(alarm_button_state == LOW){
		
		Serial.println("Alarm Snoozed");
		delay(500);//debounce	
		
		//Checks alarm is actually on so user can't snooze a alarm that isnt on 
		while(switchCaseTemp > 1 || switchCaseHum > 1){
		twoMins = millis() + 120000; //Calcuates 2 mins from now
		currentSnoozeTime = millis(); //Gets currentTime
		digitalWrite(pinBuz, 0);
		break;
		
		}
		
		}

	//Once 2 min snooze is up alarm set back on 
    while(currentSnoozeTime > twoMins){
		digitalWrite(pinBuz, 1);
		Serial.println("Alarm back on");	
		break;
	
	}
	//If Amber LED is on either temprature or humidity this is run
	while(switchCaseTemp == 2 || switchCaseHum == 2){
		digitalWrite(pinBuz, 1);
		break;
		
			
	}
	//If Red LED is on either temprature or humidity this is run
	while(switchCaseTemp == 3 || switchCaseHum == 3){
		digitalWrite(pinBuz, 1);
		break;

	
	}}
#include <Arduino.h>
//Buzzer
const int pinBuz = 13;

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

//This returns which alarm should go off
int TempColorTypeReturn;
int HumColorTypeReturn;



void alarmSetup(){
pinMode(pinBuz, OUTPUT);
Serial.println("Buzzer initialised");

}

void whichAlarm(){
	
switch(TempColorTypeReturn){
	case 1:
	digitalWrite(pinBuz, 1);
	break;
	case 2:
	digitalWrite(pinBuz, 1);
	break;
	case 3:
	digitalWrite(pinBuz, 0);
	break;
}
switch(HumColorTypeReturn){

	case 1:
	digitalWrite(pinBuz, 1);
	break;
	case 2:
	digitalWrite(pinBuz, 1);
	break;
	case 3:
	digitalWrite(pinBuz, 0);
	break;
}

}

void alarmButton(){
	    //Alarm button read in
	alarm_button_state = digitalRead(snoozeButton);
	
	//If alarm/snooze button is pressed do this
	while(alarm_button_state == LOW){
		Serial.println("Alarm Snoozed");
		digitalWrite(pinBuz, 0);
		TempColorTypeReturn = 3;
		HumColorTypeReturn = 3;
		delay(1000);//debounce	
		break;

}}

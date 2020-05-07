#include <Arduino.h>
#include <dhtValuesClass.cpp>

//Buzzer
const int pinBuz = 2;

//Button to snooze the alarm 
const int snoozeButton = 14;

//Used for the state of the output time button
int alarm_button_state = 0;

//Timeing Varibles used in the buzzer method are declared here 
int thirtySeconds = 30000;
int prevLoop = 0;

int fiveSeconds = 5000;
int prevLoopTwo = 0;




int temp;
int hum;

//This returns which alarm should go off
int TempColorTypeReturn;
int HumColorTypeReturn;



void alarmSetup(){
pinMode(pinBuz, OUTPUT);
Serial.println("Buzzer initialised");

}

void dhtClassSetupCallingOG(){
   dhtSetup();
}

void thirtySecAlarm(){
	
	while(alarm_button_state == HIGH){
	int currentTimeHere = millis();
	
	if(currentTimeHere - prevLoop > thirtySeconds){
		prevLoop = currentTimeHere;

	digitalWrite(pinBuz, 1);
	delay(1000);
		
	}
	else{
		digitalWrite(pinBuz, 0);
	}
	break;
}
}
void fiveSecAlarm(){
	
	while(alarm_button_state == HIGH){
	int currentTimeHereTwo = millis();
	
	if(currentTimeHereTwo - prevLoopTwo > fiveSeconds){
		prevLoopTwo = currentTimeHereTwo;

	digitalWrite(pinBuz, 1);
	delay(1000);
		
	}
	else{
		digitalWrite(pinBuz, 0);
	}
	break;
}
}







int tempValueCheck(){

temp = tempValueReturnDHT(); //Reads temprature stores value in "t"

if (temp > 17 && temp < 24) { //This is for the Green LED values to show all is good
		TempColorTypeReturn = 1; //Calls first switch case lighting up the green LED

	}

	else if ((temp > 15 && temp < 18) || (temp > 23 && temp < 28)) { // This is the Amber LED Values

		TempColorTypeReturn = 2; //Calls second switch case lighting up the Amber LED
		

	}

	else { //If the temperature is out of the two bounds of both the Green and Amber LED the Red LED is called

		TempColorTypeReturn = 3; //Calls switch case three light up the Red LED

	}
	return TempColorTypeReturn;
}

int humValueCheck(){
hum = humValueReturnDHT();

 if (hum >= 35 && hum <= 60) {

		HumColorTypeReturn = 1;

	}

	else if ((hum >= 25 && hum <= 34) || (hum >= 60 && hum <= 75)) {
		HumColorTypeReturn = 2;

	}

	else {
		HumColorTypeReturn = 3;
	}
    
	return HumColorTypeReturn;
}

void whichAlarm(){
    
switch(TempColorTypeReturn){
	case 1:
	//Does nothing as no buzzer is needed for green values
	break;

	case 2:
	thirtySecAlarm();
	break;
	
	case 3:
	fiveSecAlarm();
	break;
	}

switch(HumColorTypeReturn){
	case 1:
	//Does nothing as no buzzer is needed for green values
	break;
	
	case 2:
	thirtySecAlarm();
	break;
	
	case 3:
	fiveSecAlarm();
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
		delay(100);//debounce	
		break;

}}

int tempPass(){
return temp;
}

int humPass(){
return hum;
}


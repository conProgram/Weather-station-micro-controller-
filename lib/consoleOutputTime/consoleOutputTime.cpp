#include <Arduino.h>

//Output to console time Button
const int StringButton = 0;
//Output time delay is set useing this varible 
int outputTime;
//Counts output delay button presses
int outputButtonPresses = 1;
//Used for the state of the output time button
int String_button_state = 0;

//Set up class for the string output button 
void outputButtonSetup(){
    //Timed output Button
	pinMode(StringButton, INPUT);
	//outputButtonPresses = 1;
	Serial.println("Output time button initialised");
	Serial.println("Output time set to 5 Seconds by default");
	
}


int outputButton() {
    
	//Depending on how many button presses a new output time is set
	switch (outputButtonPresses) {
	case 1:
		outputTime = 5000;
		break;

	case 2:
		outputTime = 30000;
		break;

	case 3:
		outputTime = 60000;
		break;
	
	case 4:
		outputTime = 120000;
		break;
	
	case 5:
		outputTime = 300000;
		break;

    case 6: 
    outputTime = 5000;
	outputButtonPresses = 1;
	Serial.println("Output time reset ...");
    break;

	default:
		//outputButtonPresses = 1;
		//Serial.println("Output time reset ...");
		break;

	}

return outputTime;
    
  
}


void outputButtonRead(){
    String_button_state = digitalRead(StringButton);
    //If button is pressed is incrments the button counter by 1 
	while (String_button_state == LOW) {
		outputButtonPresses++;
		int upToDateOutputTime = outputButton();
		delay(500);// Used for debouncing 
		Serial.print("Output time is now: ");
		int secondOutputTime = upToDateOutputTime/1000;
		Serial.print(secondOutputTime);
		Serial.println(" seconds");
		Serial.println("Press Button again to change output time");
		break;
	}
}



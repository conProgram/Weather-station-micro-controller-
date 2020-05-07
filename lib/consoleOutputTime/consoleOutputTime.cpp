#include <Arduino.h>

//Output to console time Button
const int StringButton = 0;
//Output time delay is set useing this varible 
int outputTime;
//Counts output delay button presses
int outputButtonPresses = 1;
//Used for the state of the output time button
int String_button_state = 0;

//Varibles for button held down for a complete second per Daves request 
int startPressed = 0;    // the moment the button was pressed
int endPressed = 0;      // the moment the button was released
int holdTime = 0;        // how long the button was hold

//Set up class for the string output button 
void outputButtonSetup(){
    //Timed output Button
	pinMode(StringButton, INPUT);
	//outputButtonPresses = 1;
	Serial.println("Output time button initialised");
	Serial.println("Output time set to 5 Seconds by default");
	
}

//Method used to count the output string button presses and set the output time to the appropriate rate
int outputButton() {
    
	//Depending on how many button presses a new output time is set
	switch (outputButtonPresses) {
	case 1:
		outputTime = 5000; //5 secs
		break;

	case 2:
		outputTime = 30000; //30 secs
		break;

	case 3:
		outputTime = 60000; //60 secs
		break;
	
	case 4:
		outputTime = 120000; // 2 mins
		break;
	
	case 5:
		outputTime = 300000; // 5 min
		break;

    case 6: //Once button clicks reach 6 output time is then reset back to 5 secs
    outputTime = 5000;
	outputButtonPresses = 1;
	Serial.println("Output time reset ...");
    break;

//Default is never run 
	default:
	break;

	}

//Output time is then returned to be used in the PIR class
return outputTime;
    
  
}

//This method is just for the button itself
void outputButtonRead(){
	String_button_state = digitalRead(StringButton); //Need to add second delay
	
	if(String_button_state == HIGH){
		startPressed = millis();
	}
	
    //If button is pressed is incrments the button counter by 1 
	else {
		endPressed = millis();
		holdTime = endPressed - startPressed;


		if(holdTime > 999){
		outputButtonPresses++;
		int upToDateOutputTime = outputButton();
		delay(500);// Used for debouncing 
		//I then converted miliseconds to seconds to make it easier for the user to see the output delay time
		Serial.print("Output time is now: ");
		int secondOutputTime = upToDateOutputTime/1000;
		Serial.print(secondOutputTime);
		Serial.println(" seconds");
		Serial.println("Press Button again to change output time");
		holdTime = 0;
		
		
	}
}
}


// #include <Arduino.h>
//#include <dhtValuesClass.cpp>

// //Global 
// int switchCaseTemp;

// //Temp RGB
// const int redTemp = 16;
// const int greenTemp = 4;
// const int blueTemp = 5;

//  void tempratureSetupClass(){
// 	//Temprature RGB's
// 	pinMode(redTemp, OUTPUT);
// 	pinMode(blueTemp, OUTPUT);
// 	pinMode(greenTemp, OUTPUT);
//     Serial.println("temprature RGB initialised");
	
  	
// }

// int tempReturn(){
	
//    //float t = tempValueReturnDHT(); //Reads temprature stores value in "t"
//     
//     if (isnan(t)) {
// 		Serial.println("Failed to read Temprature from DHT sensor!");
// 		Serial.println("Ensure DHT is connected correctly");
// 		delay(2000);
// 	}

// 	else if (t > 17 && t < 24) { //This is for the Green LED values to show all is good
// 		switchCaseTemp = 1; //Calls first switch case lighting up the green LED

// 	}

// 	else if ((t > 15 && t < 18) || (t > 23 && t < 28)) { // This is the Amber LED Values

// 		switchCaseTemp = 2; //Calls second switch case lighting up the Amber LED

// 	}

// 	else { //If the temperature is out of the two bounds of both the Green and Amber LED the Red LED is called

// 		switchCaseTemp = 3; //Calls switch case three light up the Red LED

// 	}
// 	return switchCaseTemp;
	
  
// }

// void RGBTempClass(){
//     switch (switchCaseTemp) {
// 	case 1: //If switchCaseTemp is set to 1 useing the if statment above 
// 		digitalWrite(greenTemp, HIGH);
// 		digitalWrite(blueTemp, LOW);
// 		digitalWrite(redTemp, LOW);
// 		break; //Green led lights up

// 	case 2:
// 		digitalWrite(greenTemp, HIGH);
// 		digitalWrite(blueTemp, LOW);
// 		digitalWrite(redTemp, LOW);
// 		break; //Amber LED lights up

// 	case 3:
// 		digitalWrite(greenTemp, HIGH);
// 		digitalWrite(blueTemp, LOW);
// 		digitalWrite(redTemp, LOW);
// 		break; // Red LED lights up

// 		//The default is set if my previous code crashes it will become obvious as the RGB will go CYAN
// 	default:
// 		Serial.println(" Temprature Loop if statements haven't run correctly");
// 		digitalWrite(greenTemp, HIGH);
// 		digitalWrite(blueTemp, HIGH);
// 		digitalWrite(redTemp, LOW);
// 		Serial.println("FAILED !");
// 		Serial.print("Switch Case value is: ");
// 		Serial.print(switchCaseTemp);
// 		break;

// 	}}


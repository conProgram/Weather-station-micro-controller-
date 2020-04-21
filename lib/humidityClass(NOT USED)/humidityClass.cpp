// #include <Arduino.h>
 //#include <dhtValuesClass.cpp>

// //Global 
// int switchCaseHum;

// //Humidity RGB
// const int redHum = 14;
// const int greenHum = 13;
// const int blueHum = 18;

//  void humiditySetUpClass(){
  
// 	//Humdity RGB's
// 	pinMode(redHum, OUTPUT);
// 	pinMode(blueHum, OUTPUT);
// 	pinMode(greenHum, OUTPUT);
//     Serial.println("Humidity RGB initialised");
// }

// int humReturn(){

// float h = humValueReturnDHT();
// float h = 0;
//     if (isnan(h)) {
// 		Serial.println("Failed to read Humidity from DHT sensor!");
// 		Serial.println("Ensure DHT is connected correctly");
// 		delay(2000);
// 	}

// 	if (h >= 35 && h <= 60) {

// 		switchCaseHum = 1;

// 	}

// 	else if ((h >= 25 && h <= 34) || (h >= 60 && h <= 75)) {
// 		switchCaseHum = 2;

// 	}

// 	else {
// 		switchCaseHum = 3;
// 	}
    
//     return switchCaseHum;
	
  
// }

// void RGBHumClass(){
//     switch (switchCaseHum) {
// 	case 1:
// 		digitalWrite(greenHum, HIGH);
// 		digitalWrite(blueHum, LOW);
// 		digitalWrite(redHum, LOW);
// 		break;

// 	case 2:
// 		digitalWrite(greenHum, HIGH);
// 		digitalWrite(blueHum, LOW);
// 		digitalWrite(redHum, HIGH);
// 		break;

// 	case 3:
// 		digitalWrite(greenHum, LOW);
// 		digitalWrite(blueHum, LOW);
// 		digitalWrite(redHum, HIGH);
// 		break;

// 	default:
// 		Serial.print("Loop if statements haven't run correctly");
// 		digitalWrite(greenHum, HIGH);
// 		digitalWrite(blueHum, HIGH);
// 		digitalWrite(redHum, LOW);
// 		Serial.println("Failed !!!");
// 		break;

// 	}
// }

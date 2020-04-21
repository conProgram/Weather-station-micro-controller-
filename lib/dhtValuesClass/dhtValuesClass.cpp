#include <Wire.h>
//DHT Sensor Config
#include <DHT.h> //Sensor library
#define DHTPIN 15 //Pin of sensor
#define DHTTYPE DHT11   // DHT 11

DHT dht(DHTPIN, DHTTYPE); //Sets sensor pin and which type of sensor we are using in the DHL

//Global 
 float tempratureValue;
 float humidtyValue;

 void dhtSetup(){
  //DHT Sensor started
	dht.begin();
	Serial.println("Temperature and Humidity Sensor initialised");
	
  	
}
float tempValueReturnDHT(){
	
	tempratureValue = dht.readTemperature();
    return tempratureValue;
	Serial.print("Temprature value is ");
	Serial.println(tempratureValue);
}

float humValueReturnDHT(){
	
	humidtyValue = dht.readHumidity();
    return humidtyValue;
	Serial.print("Humidity value is ");
	Serial.println(humidtyValue);
}
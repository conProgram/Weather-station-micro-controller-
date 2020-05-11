#include "SD.h"
#include "FS.h"
#include <SPI.h>
#include <serverClass.cpp>


//Increments how many times the data is appended to the file 
int readingID = 0;

float temperature; //Values stored from DHT
float humidity;

WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP); //Built in server timer, can time something once connected to hotspot

String formatDate; //Gives out the date (Not working) //Dosent recogise built in feature 

String dayStamp; //What day the DHT11 Values have been taken
String timeStamp; // Time the value was taken

//SD card pin is 5 
#define SDPin 5

//Creates new instance of a file
File myFile;

//Timing varibles for two min write time 
int twoMinsToWrite = 120000;
int prevWrite = 0;



//Get temp and humidity values
void getReadings() {
  temperature = readDHTTemperature();
  humidity = readDHTHumidity();
  Serial.println("SD Card values retrived");
}

//checks to see if file exists and therefore be appended to 
void appendFile(fs::FS &fs, const char*path, const char*message) {
  Serial.printf("Appending data to File: %s\n", path);
  
  //Path is the path to the file exists
  myFile = fs.open(path, FILE_APPEND);
  if(!myFile) {
    Serial.println("Failed to open file for appending!!");
    return;
  }
  //If file is found this output is outputted
  if(myFile.print(message)) {
    Serial.println("Values appended Successfully");
  } else {
    Serial.println("Append unsuccessful");
  }
  myFile.close();

}

//Uses built in methods here
void getTimeStamp() {
  while(!timeClient.update()) {
    timeClient.forceUpdate();
  }
  formatDate = timeClient.getFormattedTime(); //This is for the date need to chaneg to format date as date is currently set to time
  //Serial.println(formatDate);

  int splitT = formatDate.indexOf("T");
  dayStamp = formatDate.substring(0, splitT); //Day stamp
  //Serial.println(dayStamp);
  timeStamp = formatDate.substring(splitT+1,formatDate.length()-1); // time Stamp
  //Serial.println(timeStamp);
}

//Same as append same as before but checks if can write to the file
void writeToFile(fs::FS &fs, const char *path, const char*message) {
  Serial.printf("Writing File: %s\n", path);

  myFile = fs.open(path, FILE_WRITE);
  if(!myFile) {
    Serial.println("Failed Writing To File....");
    return;
  }
  if(myFile.print(message)) {
    Serial.println("File Written To");
  } else {
    Serial.println("Write Failed!");
  }
  myFile.close();
}

//Format of the stored data on the micro sd card
void logSDCard () {
  readingID++;
  dataMessage = "The reading is: " + String (readingID) + " The time the reading took place: " + String(dayStamp) +  " The temperature value is: " 
   + String(temperature) +  " The humidity Value is: " + String(humidity) + "\r\n";

  //Serial.println(dataMessage);
  appendFile(SD, "/data.txt" , dataMessage.c_str());
}

//Method used to initalize SD card and open the .txt file for storage 
void SDcardsetup() {
  SD.begin(SDPin);
  if(!SD.begin(SDPin)) {
    Serial.println("Card mount failed");
    return;
  }
  uint8_t cardType = SD.cardType();
  if (cardType == CARD_NONE) {
    Serial.println("SD not attached");
    return;
  }
  Serial.println("Initialising SD card");
  if(!SD.begin(SDPin)) {
    Serial.println("Initialisation Failed");
    return;
  }

  myFile = SD.open("/data.txt");
  if(!myFile) {
    Serial.println("File doesn't exist");
    Serial.println("Creating File.....");
    writeToFile(SD, "/data.txt", "New reading started\r\n");
  } else {
    Serial.println("File Already Exists");
  }
  myFile.close();

  getReadings();
  logSDCard();

  readingID++;//increments reading number 
  Serversetup();
}

//Passing all set up methods to the main class
void setUpPassing(){
  bigSetUpMethod();
}
//Passing looping methods to the main class
void loopPassing(){
bigLoopMethod();
}

void twoMinsSDCardWrite(){
  int currentTimeForSDWrite = millis();
	if(currentTimeForSDWrite - prevWrite > twoMinsToWrite){
		prevWrite = currentTimeForSDWrite;
    getReadings();
    getTimeStamp();
    logSDCard();
    Serial.println("Temprature and humidty now stored on SD card");
    Serial.println("Values are stored every 2 mins");

	}
}

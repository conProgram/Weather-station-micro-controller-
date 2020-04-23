#include "SD.h"
#include "FS.h"
#include <SPI.h>
#include <serverClass.cpp>


//  uint64_t uS_TO_S_FACTOR = 1000000;
//  uint64_t TIME_TO_SLEEP = 600;

//Increments how many times the data is appended to the file 
RTC_DATA_ATTR int readingID = 0;


float temperature; //Values stored from DHT
float humidity;

//  WiFiUDP ntpUDP;
//  NTPClient timeClient(ntpUDP); //Built in server timer, can time something once connected to hotspot

String formatDate; //Gives out the date (Not working) //Dosent recogise built in feature 
String dayStamp; //What day the DHT11 Values have been taken
String timeStamp; // Time of it

//SD card pin is 5 
#define SDPin 5

//Creates new instance of a file
File myFile;


//Get values
void getReadings() {
 // Need to parse dht values here
  temperature = 10;
  humidity = 30;
  
  Serial.print("Temperature: ");
  Serial.println(temperature);
  Serial.print("humidity: ");
  Serial.println(humidity);
}

//checks to see if file exists and therefore be appended to 
void appendFile(fs::FS &fs, const char*path, const char*message) {
  Serial.printf("Appending to File: %s\n", path);
  
  //Path is the path to the file exists
  myFile = fs.open(path, FILE_APPEND);
  if(!myFile) {
    Serial.println("Failed to open file for appending!!");
    return;
  }
  if(myFile.print(message)) {
    Serial.println("Message appended Successfully");
  } else {
    Serial.println("Append unsuccessful");
  }
  myFile.close();

}

// //Uses built in methods here
// void getTimeStamp() {
//   while(!timeClient.update()) {
//     timeClient.forceUpdate();
//   }
//   formatDate = timeClient.getFormattedTime(); //This is for the date need to chaneg to format date as date is currently set to time
//   Serial.println(formatDate);

//   int splitT = formatDate.indexOf("T");
//   dayStamp = formatDate.substring(0, splitT);
//   Serial.println(dayStamp);
//   timeStamp = formatDate.substring(splitT+1,formatDate.length()-1);
//   Serial.println(timeStamp);
// }

//Same as append same as before but checks if can write to
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
  dataMessage = String (readingID) + "," //DayStamp dosen't work because .getFormatted dat e dosen work
   + String(temperature) +  "," + String(humidity) + "\r\n";

  Serial.print("Save Date: ");
  Serial.println(dataMessage);
  appendFile(SD, "/data.txt" , dataMessage.c_str());
}

//Calls the other methods and connects to internet 
void SDcardsetup() {
  
  // timeClient.begin();
  // timeClient.setTimeOffset(3600);

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
    writeToFile(SD, "/data.txt", "Reading ID, Date, Hour, Temperature \r\n");
  } else {
    Serial.println("File Already Exists");
  }
  myFile.close();

  //esp_sleep_enable_timer_wakeup(TIME_TO_SLEEP * uS_TO_S_FACTOR);

  getReadings();
  //getTimeStamp();
  logSDCard();

  readingID++;
  Serversetup();

  //Serial.println("Sleeping....");
  //esp_deep_sleep_start();
}

//Passing all set up methods to the main class
void setUpPassing(){
  bigSetUpMethod();
}
//Passing looping methods to the main class
void loopPassing(){
bigLoopMethod();
}

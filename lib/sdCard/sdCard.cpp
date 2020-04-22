#include "SD.h"
#include "FS.h"
#include <SPI.h>
#include <WiFi.h>
#include <NTPClient.h>
#include <WiFiUdp.h>


uint64_t uS_TO_S_FACTOR = 1000000;
uint64_t TIME_TO_SLEEP = 600;

const char*ssid = "LewisiPhone";
const char*password = "password123";

RTC_DATA_ATTR int readingID = 0;
String dataMessage;

float temperature;
float humidity;

WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP);

String formatDate;
String dayStamp;
String timeStamp; 

//SD card pin is 5 
#define SDPin 5
File myFile;


void getReadings() {
  temperature = 10;
  Serial.print("Temperature: ");
  Serial.println(temperature);
}

void appendFile(fs::FS &fs, const char*path, const char*message) {
  Serial.printf("Appending to File: %s\n", path);
  
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

void getTimeStamp() {
  while(!timeClient.update()) {
    timeClient.forceUpdate();
  }
  formatDate = timeClient.getFormattedTime();
  Serial.println(formatDate);

  int splitT = formatDate.indexOf("T");
  dayStamp = formatDate.substring(0, splitT);
  Serial.println(dayStamp);
  timeStamp = formatDate.substring(splitT+1,formatDate.length()-1);
  Serial.println(timeStamp);
}

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

void logSDCard () {
  dataMessage = String (readingID) + "," + String(dayStamp)
  + "," + String(timeStamp) + "," + String(temperature) + "\r\n";

  Serial.print("Save Date: ");
  Serial.println(dataMessage);
  appendFile(SD, "/data.txt" , dataMessage.c_str());
}

void SDcardsetup() {
  
  Serial.print("Connecting.....");
  Serial.print(ssid);
  WiFi.begin(ssid,password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print("Connecting to host");
  }
  Serial.println("");
  Serial.println("WiFi Connected");

  timeClient.begin();
  timeClient.setTimeOffset(3600);

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

  esp_sleep_enable_timer_wakeup(TIME_TO_SLEEP * uS_TO_S_FACTOR);

  getReadings();
  getTimeStamp();
  logSDCard();

  readingID++;

  Serial.println("Sleeping....");
  esp_deep_sleep_start();
}


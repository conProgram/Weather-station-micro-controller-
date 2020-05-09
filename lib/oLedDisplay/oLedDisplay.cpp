#include <Arduino.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <dhtValuesClass.cpp>

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels

//Values to store temprature and humidity 
int tempValue;
int humValue;

//Used for display changeing 
int led_change_button_state = 0;
int displayButtonPresses = 1;
const int displayButtonPin = 32;  

//This varible is used to determin what to output on the OLED display 
int theOutput;
String outputType;
String datatype;




// Declaration for an SSD1306 display connected to I2C (SDA, SCL pins)
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

void screenSetup(){

if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) { // Address 0x3D for 128x64
    Serial.println(F("SSD1306 allocation failed"));
    for(;;);
  }

pinMode(displayButtonPin, INPUT);
	Serial.println("displayButton set up");  
}




int tempValueReturnDHT(){
  tempValue = tempValueReturnFromDHTClass();
  return tempValue;
}

int humValueReturnDHT(){
  humValue = humValueReturnFromDHTClass();
  return humValue;
}



void displayButton(){
  led_change_button_state = digitalRead(displayButtonPin);

  if(led_change_button_state == LOW){
    displayButtonPresses++;
    delay(500); // debounce 
  }
}

//Used to detrmin which int value to show
int whichDisplayValue(){
  switch (displayButtonPresses){
    case 1:
    theOutput = tempValue;
    break;
    case 2:
    
    theOutput = humValue;
    break;
    case 3:
    displayButtonPresses = 1;
    break;
  }
  return theOutput;
}

//Used to determin which data type to be displayed
String whichDisplayType(){
  switch (displayButtonPresses){
    case 1:
    outputType = "The Temprature is: ";
    datatype = " degrees celsius";
    break;
    case 2:
    outputType = "The humidity is: ";
    datatype = " %";
    break;
  }
  return outputType;
  
}


void screenOutput(){
  display.clearDisplay();

  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(0, 10);
  // Display static text
  display.println(outputType);
  display.print(theOutput);  
  display.println(datatype);
  display.display();
}

void mainOledMethod(){
  displayButton();
  whichDisplayValue();
  whichDisplayType();
  screenOutput();

}
#include <Arduino.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <dhtValuesClass.cpp>

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels

int tempValue;
int humValue;

// Declaration for an SSD1306 display connected to I2C (SDA, SCL pins)
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

void screenSetup(){

if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) { // Address 0x3D for 128x64
    Serial.println(F("SSD1306 allocation failed"));
    for(;;);
  }

  delay(2000);
  display.clearDisplay();

  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(0, 10);
  // Display static text
  display.print("Temprature is: ");
  display.println(tempValue); 
  display.print("Humidity is: ");
  display.println(humValue); 
  display.display();

}


void screenOutput(){

}

int tempValueReturnDHT(){
  tempValue = tempValueReturnFromDHTClass();
  return tempValue;
}

int humValueReturnDHT(){
  humValue = humValueReturnFromDHTClass();
  return humValue;
}
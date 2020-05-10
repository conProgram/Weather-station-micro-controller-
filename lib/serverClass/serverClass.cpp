#include "WiFi.h"
#include "ESPAsyncWebServer.h"
#include <Adafruit_Sensor.h>
#include <NTPClient.h>
#include <WiFiUdp.h>
#include <pirSensorClass.cpp>

//This passes all the setup methods from the PirClass into here to then be passes the main setup()
 void bigSetUpMethod(){
 setupPirClass();
 }
//This passes all the Loop methods from the PirClass into here to then be passes the main loop()
 void bigLoopMethod(){
 loopingPirSensor();
 }

//All sever code here

//Hotspot credentials are set


//Need to change from hotpot to external server 
const char*ssid = "CiPhone"; //My hotspot name
const char*password = "conyers98"; //Hotspot password

//Timeing varibles
int thirtySecondServerUpdate = 30000;
int prevTimer = 0; 

//To string varibles for web code
String newTempString;
String newHumString;


String dataMessage;
AsyncWebServer server(80);

//Passes the temprature values in from the pirSensor Class
int readDHTTemperature() {
  float t = tempPassing();
    return int(t);
  
}
//Same as above with humidity
int readDHTHumidity() {
  float h = humPassing();
    return int(h);

}


//Converts int values to strings so can be used on the web server 
String stringConvertTemp(){
//if statment used to update values every 30 seconds  
int currentTimeSever = millis();
if(currentTimeSever - prevTimer > thirtySecondServerUpdate){
prevTimer = currentTimeSever;
int oldValue = readDHTTemperature();
newTempString = String(oldValue);


}
return newTempString;}

String stringConvertHum(){
int currentTimeSeverTwo = millis(); 
if(currentTimeSeverTwo - prevTimer > thirtySecondServerUpdate){  
prevTimer = currentTimeSeverTwo;
int oldValueTwo = readDHTHumidity();
newHumString = String(oldValueTwo);

}

return newHumString;}


//The HTML code for the web server page
const char index_html[] PROGMEM = R"rawliteral(
<!DOCTYPE HTML><html>
<head>
  <meta name="viewport" content="width=device-width, initial-scale=1">
  <link rel="stylesheet" href="https://use.fontawesome.com/releases/v5.7.2/css/all.css" integrity="sha384-fnmOCqbTlWIlj8LyTjo7mOUStjsKC4pOpQbqyi7RrhN7udi9RwhKkMHpvLbHG9Sr" crossorigin="anonymous">
  <style>
    html {
     font-family: Arial;
     display: inline-block;
     margin: 0px auto;
     text-align: center;
    }
    h2 { font-size: 3.0rem; }
    p { font-size: 3.0rem; }
    .units { font-size: 1.2rem; }
    .dht-labels{
      font-size: 1.5rem;
      vertical-align:middle;
      padding-bottom: 15px;
    }
  </style>
</head>
<body>
  <h2>ESP32 DHT Server</h2>
  <p>
    <i class="fas fa-thermometer-half" style="color:#059e8a;"></i> 
    <span class="dht-labels">Temperature</span> 
    <span id="temperature">%TEMPERATURE%</span>
    <sup class="units">&deg;C</sup>
  </p>
  <p>
    <i class="fas fa-tint" style="color:#00add6;"></i> 
    <span class="dht-labels">Humidity</span>
    <span id="humidity">%HUMIDITY%</span>
    <sup class="units">%</sup>
  </p>
</body>
<script>
setInterval(function ( ) {
  var xhttp = new XMLHttpRequest();
  xhttp.onreadystatechange = function() {
    if (this.readyState == 4 && this.status == 200) {
      document.getElementById("temperature").innerHTML = this.responseText;
    }
  };
  xhttp.open("GET", "/temperature", true);
  xhttp.send();
}, 10000 ) ;

setInterval(function ( ) {
  var xhttp = new XMLHttpRequest();
  xhttp.onreadystatechange = function() {
    if (this.readyState == 4 && this.status == 200) {
      document.getElementById("humidity").innerHTML = this.responseText;
    }
  };
  xhttp.open("GET", "/humidity", true);
  xhttp.send();
}, 10000 ) ;
</script>
</html>)rawliteral";



// Replaces placeholder with DHT values
String processor(const String& var){
  
  //Defines the temprature and humidity based on the methods at the top of code
  if(var == "TEMPERATURE"){
    return stringConvertTemp();
  }
  else if(var == "HUMIDITY"){
    return stringConvertHum();
  }
  return String();
}


//This method sets up the server 
void Serversetup(){
  
  // Connect to Wi-Fi
  WiFi.begin(ssid, password);
  
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi..");
    break;
  }
  
  Serial.print("Enter this code into your broswer to view WEB server: ");
  //Gets the web address to view the web server on your connected hotspot
  Serial.println(WiFi.localIP());

  server.on("/", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send_P(200, "text/html", index_html, processor);
  });
  server.on("/temperature", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send_P(200, "text/plain", stringConvertTemp().c_str());
  });
  server.on("/humidity", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send_P(200, "text/plain", stringConvertHum().c_str());
  });

  // Start server
  server.begin();
}



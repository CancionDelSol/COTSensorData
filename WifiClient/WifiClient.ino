#include <WiFi.h>
#include <WiFiAP.h>
#include <WiFiClient.h>
#include <WiFiGeneric.h>
#include <WiFiMulti.h>
#include <WiFiScan.h>
#include <WiFiServer.h>
#include <WiFiSTA.h>
#include <WiFiType.h>
#include <WiFiUdp.h>

#include <HTTPClient.h>

#include "COTWifiInfo.h"

#define BUFFER_SIZE 4

/*
 * WIFI Client
 * Attached via serial COM port to the laptop running
 * the telemetry JAR. A request will be made via serial
 * port to this ESP module. 
 */



// Setup
void setup() {
  // Set Built-In LED as output
  pinMode(LED_BUILTIN, OUTPUT);

  // Begin serial com
  Serial.begin(BAUD_RATE);

  // Notify connecting
  Serial.println("Connecting");

  // Connect to wifi
  WiFi.begin(SSID, PWD);

  // Connecting "animation"
  while(WiFi.status() != WL_CONNECTED) { 
    delay(1250);
    Serial.print(".");
  }

  // Notify successful connection
  Serial.println("");
  Serial.print("Connected to server with IP Address: ");
  Serial.println(WiFi.localIP());
}

// Loop
int flip = 0;
String serverPath = "http://192.168.4.1/";
String ledOnEndpoint = "led/on";
String ledOffEndpoint = "led/off";
String sensorDataEndpoint = "sensordata/";

// Use integers for individual requests
int DATA_REQUEST = 1;
int LED_FLIP = 2;
// TODO : Add the rest of the encryptions

// Main loop
void loop() {
  if (WiFi.status() == WL_CONNECTED) {
    String curEndpoint;

    // Read serial and make
    //  appropriate request
    int* buffer = (int*)malloc(sizeof(int) * BUFFER_SIZE);
    int index = 0;
    while (Serial.available() > 0) {
      buffer[index++] = (int)Serial.read();
    }

    String resp;
    if (index > 0) {
      switch(buffer[0]) {
        case 0:
          // Invalid
          Serial.print("No Action for input 0");
          break;
        case 1:
          resp = FlipLED();
          Serial.print(resp);
          break;
        case 2:
          break;
        case 3:
          // Make raw data request
          //  index will be the offset
          //  for encryption type
          resp = GetDataFromSensorProvider(index - 1);
          Serial.print(resp);
          break;
      }
    }
  }
}

// 0 - No encryption
String GetDataFromSensorProvider(int encryption) {
  String curEndpoint = serverPath + sensorDataEndpoint;

  if (encryption > 0) {
    curEndpoint += "encType" + String(encryption);
  }
  
  return httpGETRequest(curEndpoint.c_str());
}

// Flip the LED and return server's
//  response
String FlipLED() {
  String curEndpoint = serverPath;
    
  if (flip == 0) {
    flip = 1;
    curEndpoint += sensorDataEndpoint;
  } else {
    flip = 0;
    curEndpoint += ledOnEndpoint;
  }

  return httpGETRequest(curEndpoint.c_str());
}

String httpGETRequest(const char* serverName) {
  WiFiClient client;
  HTTPClient http;
    
  // Your Domain name with URL path or IP address with path
  http.begin(client, serverName);
  
  // Send HTTP POST request
  int httpResponseCode = http.GET();
  
  String payload = "{}"; 
  
  if (httpResponseCode>0) {
    Serial.print("HTTP Response code: ");
    Serial.println(httpResponseCode);
    payload = http.getString();
  }
  else {
    Serial.print("Error code: ");
    Serial.println(httpResponseCode);
  }
  // Free resources
  http.end();

  return payload;
}

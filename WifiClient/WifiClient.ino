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

// Use macros for individual requests
#define NO_ENC 0
#define ENC_TYPE_ONE 1

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

// Integer to track LED flip state
int flip = 0;

// Endpoints
String serverPath = "http://192.168.4.1/";
String ledOnEndpoint = "led/on";
String ledOffEndpoint = "led/off";
String sensorDataEndpoint = "sensordata/";

// Here is the sensor data
String sensorData = "Sensor Data Test";

// Main loop
void loop() {
  if (WiFi.status() == WL_CONNECTED) {
    String curEndpoint;

    // Read serial and make
    //  appropriate request
    int req = -1;
    while (Serial.available() > 0) {
      req = (int)Serial.read();
    }

    // Make raw data request
    //  index will be the offset
    //  for encryption type
    String resp = GetDataFromSensorProvider(req);

    // Communicate back response
    Serial.print(resp);
  }
}

// 0 - No encryption
String GetDataFromSensorProvider(int encryption) {
  String curEndpoint = serverPath + sensorDataEndpoint;

  if (encryption > NO_ENC) {
    curEndpoint += "encType" + String(encryption) + "/";
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
    payload = http.getString();
  }

  // Free resources
  http.end();

  return payload;
}
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
String sensorDataEnpoint = "sensordata/";
String encryptedEndpoint = "encrypted";

// Main loop
void loop() {
  if (WiFi.status() == WL_CONNECTED) {
    String curEndpoint;

    if (flip == 0) {
      flip = 1;
      curEndpoint = serverPath + ledOffEndpoint;
      
      
    } else {
      flip = 0;
      curEndpoint = serverPath + ledOnEndpoint;
      
    }
  
    // Make http get call
    String html = httpGETRequest(curEndpoint.c_str());
  
    // Log
    Serial.println(html);

    
  }

    // 5 seconds between calls
    delay(5000);
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

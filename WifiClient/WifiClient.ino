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

#include "COTStd.h"

/*
 * WIFI Client
 * Attached via serial COM port to the laptop running
 * the telemetry JAR. A request will be made via serial
 * port to this ESP module. 
 */

// Setup
void setup() {
  // This delay helps when
  //  first setting up the
  //  entire experiment
  delay(2500);
  
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
  SetLEDHigh();
}

// Endpoints
String serverPath = "http://192.168.4.1/";
String sensorDataEndpoint = "sensordata/";

// Here is the sensor data
String sensorData = "Sensor Data Test";

// Main loop
void loop() {
  if (WiFi.status() == WL_CONNECTED) {
    String curEndpoint;

    // Read serial and make
    //  appropriate request
    String req = "";
    bool hasRequest = false;
    if (Serial.available() > 0) {
      req = Serial.readString();
      hasRequest = true;
    }

    if (!hasRequest) {
      return;
    }

    SetLEDLow();

    // Make raw data request
    //  index will be the offset
    //  for encryption type
    String startTime = String(millis(), DEC);
    String resp = GetDataFromSensorProvider(req);
    resp.trim();
    String endTime = String(millis(), DEC);

    // Communicate back response
    SendMsgSerial(startTime + " " + resp + " " + endTime);

    SetLEDHigh();
  }
}

String GetDataFromSensorProvider(String request) {
  String curEndpoint = serverPath + sensorDataEndpoint;

  if (request.indexOf("CurrentTime") >= 0) {
    curEndpoint += "CurrentTime/";
  } else {
    curEndpoint += "encType" + String(request) + "/";
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

void SendMsgSerial(String msg) {
  Serial.print("<" + msg + ">");
}
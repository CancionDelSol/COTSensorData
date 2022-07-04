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

/*
 * WIFI Server
 * Attached to RPi via serial COM port
 * RPi runs the telemetry JAR, which listens
 * for serial prompts coming from the ESP module
 */

// Includes
#include "COTWifiInfo.h"

// Create Wifi server
WiFiServer server(80);

// Variable to store the HTTP request
String header;

// Current time
unsigned long currentTime = millis();

// Previous time
unsigned long previousTime = 0; 

// Timeout time
const long timeoutTime = 2000;

void setup() {
  // Begin serial communication
  Serial.begin(115200);

  // Set built in LED as output
  pinMode(LED_BUILTIN, OUTPUT);

  // Connect to Wi-Fi network with SSID and password
  Serial.print("Starting Access Point");
  
  // Remove the password parameter, if you want the AP (Access Point) to be open
  WiFi.softAP(SSID, PWD);

  // Get IP address
  IPAddress IP = WiFi.softAPIP();

  // Log
  Serial.print("AP IP address: ");
  Serial.println(IP);

  // Start server
  server.begin();
}

void loop(){
  // Listen for incoming clients
  WiFiClient client = server.available();

  // Log
  Serial.println("Checking for client");
  
  // Check for new client
  if (client) {

    // Log
    Serial.println("New Client.");          

    // Incoming data buffer
    String currentLine = "";

    // Loop while the client is connected
    while (client.connected()) {

      // Check to see if there are bytes
      //  in the incoming buffer
      if (client.available()) {

        // Read from client
        char c = client.read();

        // Log
        Serial.write(c);

        // Append to header
        header += c;

        // End of transmission
        if (c == '\n') {
          // End of HTTP request
          if (currentLine.length() == 0) {
            
            // Send response
            client.println("HTTP/1.1 200 OK");
            client.println("Content-type:text/html");
            client.println("Connection: close");
            client.println();
            
            // Send encrypted data back
            String response;
            if (header.indexOf("GET /sensordata/encType1") >= 0) {
              Serial.println("Get encrypted data");
              response = "encrypted data";

            // Send unencrypted data back
            } else if (header.indexOf("GET /sensordata/") >= 0) { 
              Serial.println("Get unencrypted data");
              response = "unencrypted data";

            // Turn the len on
            } else if (header.indexOf("GET /led/on") >= 0) {
              Serial.println("Setting LED on");
              SetLEDHigh();
              response = "LED On";

            // Turn the led off
            } else if (header.indexOf("GET /led/off") >= 0) {
              Serial.println("Setting LED low");
              SetLEDLow();
              response = "LED Off";
              
            }
            
            // HTML containing response
            client.println("<!DOCTYPE html><html>");
            client.println("<head><meta name=\"viewport\" content=\"width=device-width, initial-scale=1\"></head>");
            client.println("<link rel=\"icon\" href=\"data:,\">");
            
            // Start of body
            client.println("<body>");

            // Header
            client.println("<h1>COT Project</h1>");
            
            // Test response for now
            client.println("<p>" + response + "</p>");
            
            // End body
            client.println("</body>");

            // End html
            client.println("</html>");
            
            // The HTTP response ends with another blank line
            client.println();
            
            // Break out of the while loop
            break;
          } 

          // Otherwise, clear the current line
          else { 
            currentLine = "";
          }
        } else if (c != '\r') {  
          // Add to current line
          currentLine += c;
        }
      }
    }
    
    // Clear the header variable
    header = "";
    
    // Close the connection
    client.stop();

    // Log
    Serial.println("Client disconnected.");
    Serial.println("");
  }
}

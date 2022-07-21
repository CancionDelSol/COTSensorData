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
  delay(250);
  
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

bool guiDisplayFlip = true;
void loop(){
  // Listen for incoming clients
  WiFiClient client = server.available();

  // Log
  if (guiDisplayFlip) {
    Serial.println("Checking for client");
    guiDisplayFlip = false;
  }
  
  // Check for new client
  if (client) {

    // Log
    Serial.println("New Client.");

    // Current line read from client
    String currentLine;

    // Loop while the client is connected
    while (client.connected()) {

      // Check to see if there are bytes
      //  in the incoming buffer
      if (client.available()) {

        // Read from client
        char c = client.read();

        // Add received time to
        //  response
        String response = String(millis(), DEC);
        response += " ";
        
        // Append to header
        header += c;

        // End of transmission
        if (c == '\n') {
          
          // End of HTTP request
          if (currentLine.length() == 0) {
            
            Serial.println(header);
            
            // Send response
            client.println("HTTP/1.1 200 OK");
            client.println("Content-type:text/html");
            client.println("Connection: close");
            client.println();
            
            // Send unencrypted data back
            if (header.indexOf("GET /sensordata/encTypeNone") >= 0) {
              Serial.println("Get unencrypted data");
              response += "Unencrypted Data";

            // Send aes encrypted data back
            } else if (header.indexOf("GET /sensordata/encTypeAES") >= 0) { 
              Serial.println("Get AES encrypted data");
              response += "AES Encrypted Data";

            // Send des data back
            } else if (header.indexOf("GET /sensordata/encTypeDES") >= 0) { 
              Serial.println("Get DES encrypted data");
              response += "DES Encrypted Data";

            // Send des data back
            } else if (header.indexOf("GET /sensordata/encTypeECC") >= 0) { 
              Serial.println("Get ECC encrypted data");
              response += "ECC Encrypted Data";

            // Turn the len on
            } else if (header.indexOf("GET /led/on") >= 0) {
              Serial.println("Setting LED on");
              SetLEDHigh();
              response += "LED On";

            // Turn the led off
            } else if (header.indexOf("GET /led/off") >= 0) {
              Serial.println("Setting LED low");
              SetLEDLow();
              response += "LED Off";

            } else if (header.indexOf("GET /curTime") >= 0) {
              Serial.println("Sending current time");
              response += String(millis(), DEC);
              
            } else {
              Serial.println("Not recognized: " + header);
              response += "Not recognized: " + header;
            }

            response += " ";
            response += String(millis(), DEC);
            
            client.println(response);
            
            // The HTTP response ends with another blank line
            client.println();

            // Flip to looking for client
            guiDisplayFlip = true;
            
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

void printLocalTime(){
  struct tm timeinfo;
  if(!getLocalTime(&timeinfo)){
    Serial.println("Failed to obtain time");
    return;
  }
  Serial.println(&timeinfo, "%A, %B %d %Y %H:%M:%S");
  Serial.print("Day of week: ");
  Serial.println(&timeinfo, "%A");
  Serial.print("Month: ");
  Serial.println(&timeinfo, "%B");
  Serial.print("Day of Month: ");
  Serial.println(&timeinfo, "%d");
  Serial.print("Year: ");
  Serial.println(&timeinfo, "%Y");
  Serial.print("Hour: ");
  Serial.println(&timeinfo, "%H");
  Serial.print("Hour (12 hour format): ");
  Serial.println(&timeinfo, "%I");
  Serial.print("Minute: ");
  Serial.println(&timeinfo, "%M");
  Serial.print("Second: ");
  Serial.println(&timeinfo, "%S");

  Serial.println("Time variables");
  char timeHour[3];
  strftime(timeHour,3, "%H", &timeinfo);
  Serial.println(timeHour);
  char timeWeekDay[10];
  strftime(timeWeekDay,10, "%A", &timeinfo);
  Serial.println(timeWeekDay);
  Serial.println();
}
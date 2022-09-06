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
#include "COTStd.h"
#include "AESLib.h"
#include "tinyECC.h"

// Create Wifi server
WiFiServer server(80);

// Variable to store the HTTP request
String header;

// Timeout time
const long timeoutTime = 2000;

void setup() {
  // Copy text in the readBuffer
  //  into the character array used
  //  for AES encryption
  sprintf((char*)clearText, "%s", readBuffer);
  
  // Allow time for serial moniter to react
  //  top opening serial channel. Some serial
  //  output gets dropped from the windows client
  //  otherwise
  delay(250);

  // Initialize encryption library
  aes_init();
  
  // Begin serial communication
  Serial.begin(BAUD);

  // Set built in LED as output
  pinMode(LED_BUILTIN, OUTPUT);

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
    SetLEDHigh();

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
            if (header.indexOf("GET /sensordata/CurrentTime") >= 0) {
              Serial.println("Get current server time");
              response += "Time Request";

            } else if (header.indexOf("GET /sensordata/encTypeNone") >= 0) {
              Serial.println("Get unencrypted data");
              response += "Unencrypted Data";

            // Send aes encrypted data back
            } else if (header.indexOf("GET /sensordata/encTypeAES") >= 0) { 
              Serial.println("Get AES encrypted data");

              uint16_t len = encryptToCipherText((char*)clearText, 18, aes_iv);
              String suffix = (const char*)cipherText;
              response += suffix;

            // Send des data back
            } else if (header.indexOf("GET /sensordata/encTypeDES") >= 0) { 
              Serial.println("Get DES encrypted data");
              _desLib.encrypt(_desOut, _desIn, _desKey);
              response += "DES Enc Data";

            // Send des data back
            } else if (header.indexOf("GET /sensordata/encTypeECC") >= 0) {
              Serial.println("Get ECC encrypted data");

              // Encrypt using elliptic curve cryptography
              tinyECC tE;
              tE.plaintext = "ECC encrypted text";
              tE.encrypt();
              
              response += tE.ciphertext;

            } else if (header.indexOf("GET /sensordata/encTypeCurrentTime/") >= 0) {
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
    SetLEDLow();
  }
}

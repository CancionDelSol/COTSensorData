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

// AES Encryption support
byte enc_iv[N_BLOCK] = { 0, 0, 0, 0,
                         0, 0, 0, 0,
                         0, 0, 0, 0,
                         0, 0, 0, 0 };

// Create Wifi server
WiFiServer server(80);

// Variable to store the HTTP request
String header;

// Timeout time
const long timeoutTime = 2000;

void setup() {
  // General Initialization
  GenInit();
  
  // Serial logging
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
        response += COMM_DELIM;
        
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
              response += "Time-Request";

            } else if (header.indexOf("GET /sensordata/encTypeNone") >= 0) {
              Serial.println("Get unencrypted data");
              response += "Unencrypted-Data";

            // Send aes encrypted data back
            } else if (header.indexOf("GET /sensordata/encTypeAES") >= 0) { 
              Serial.println("Get AES encrypted data");

              String input = "DEADBEEF";
              char buffer[512];
              sprintf(buffer, "%s", input);
              
              String output = encryptToCipherText(buffer, String(buffer).length(), enc_iv);
          
              // Clear the encryption
              //  initialization vector
              for (int i = 0; i < 16; i++) {
                enc_iv[i] = 0;
              }
          
              // Append response
              response += output;

            // Send des data back
            } else if (header.indexOf("GET /sensordata/encTypeDES") >= 0) { 
              
              _desLib.encrypt(_desOut, _desIn, _desKey);
              char chars[9];

              std::memcpy(chars, _desOut, 8);
              chars[8] = '\0';
              String part = String(chars);
              Serial.println("Get-DES-encrypted-data: " + part);
              response += part;

            // Send ecc data back
            } else if (header.indexOf("GET /sensordata/encTypeECC") >= 0) {
              Serial.println("Get-ECC-encrypted-data");

              // Encrypt using elliptic curve cryptography
              tinyECC tE;
              tE.plaintext = "DEADBEEF";
              tE.encrypt();

              tE.genSig();

              tE.verifySig();
              tE.decrypt();
              
              //response += String(tE.Sig[0])+"!"+String(tE.Sig[1])+"!";
              response += tE.plaintext;

            } else if (header.indexOf("GET /sensordata/encTypeCurrentTime/") >= 0) {
              Serial.println("Sending current time");
              response += String(millis(), DEC);
              
            } else {
              Serial.println("Not recognized: " + header);
              response += "Not-recognized:" + header;
            }

            response += COMM_DELIM;
            response += String(millis(), DEC);

            Serial.println(response);
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
    //SetLEDLow();
  }
}

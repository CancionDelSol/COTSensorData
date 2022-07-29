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

#include "AESLib.h"

#define INPUT_BUFFER_LIMIT (128 + 1)

unsigned char clearText[INPUT_BUFFER_LIMIT] = {0}; // THIS IS INPUT BUFFER (FOR TEXT)
unsigned char cipherText[2*INPUT_BUFFER_LIMIT] = {0}; // THIS IS OUTPUT BUFFER (FOR BASE64-ENCODED ENCRYPTED DATA)
unsigned char readBuffer[18] = "AES Enc Data";

#define BAUD 115200

/*
 * AES encryption support
 * Pulled from example under
 *  the github repo -> https://github.com/suculent/thinx-aes-lib.git
 */
AESLib _aesLib;
byte aes_key[]       = { 0x6D, 0x12, 0xF7, 0x09,
                         0x3C, 0xAB, 0x88, 0xCF,
                         0xAB, 0xF7, 0x15, 0xBC,
                         0x09, 0x1F, 0x00, 0xAA };

byte aes_iv[N_BLOCK] = { 0x0A, 0x0B, 0x0C, 0x0D,
                         0x0C, 0x0D, 0x0E, 0x10,
                         0x11, 0x12, 0x13, 0x14,
                         0x15, 0x16, 0x17, 0x18 };

/*
 * Method to encrypt character pointer (text)
 *  to cipher text
 */
uint16_t encryptToCipherText(char* msg, uint16_t msgLen, byte iv[]) {
  // Log to serial client
  Serial.println("Calling encrypt (string)...");

  // Encrypt the text in the pointer's
  //  location and place into byt array
  int cipherlength =_aesLib.encrypt((byte*)msg, msgLen, (char*)cipherText, aes_key, sizeof(aes_key), iv);
  
  // Return the cipher length
  return cipherlength;
}

/*
 * Decrypt byte array into 
 */
uint16_t decryptToClearText(byte msg[], uint16_t msgLen, byte iv[]) {
  // Log to serial client
  Serial.print("Calling decrypt... ");

  // Do the decryption and place output into
  //  
  uint16_t dec_bytes =_aesLib.decrypt(msg, msgLen, (char*)clearText, aes_key, sizeof(aes_key), iv);
  Serial.print("Decrypted bytes: "); Serial.println(dec_bytes);
  return dec_bytes;
}

// Generate IV (once)
void aes_init() {
  _aesLib.gen_iv(aes_iv);
  _aesLib.set_paddingmode((paddingMode)0);
}

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
/*
 * Bluetooth server for ESP32 module
 * Feeds back data similar to the Wifi module
 */

#include "BluetoothSerial.h"
#include "COTStd.h"
#include "AESLib.h"

/*
 * From online resource: https://randomnerdtutorials.com/esp32-bluetooth-classic-arduino-ide/ 
 */
#if !defined(CONFIG_BT_ENABLED) || !defined(CONFIG_BLUEDROID_ENABLED)
#error Bluetooth is not enabled! Please run `make menuconfig` to and enable it
#endif

BluetoothSerial SerialBT;

#define BAUD 115200

// Timeout time
const long timeoutTime = 2000;

void setup() {
  // Copy text in the readBuffer
  //  into the character array used
  //  for AES encryption
  sprintf((char*)clearText, "%s", readBuffer);
  
  // Allow time for serial moniter to react
  //  to opening serial channel. Some serial
  //  output gets dropped from the windows client
  //  otherwise
  delay(250);

  // Initialize encryption library
  aes_init();
  
  // Begin serial communication
  Serial.begin(BAUD);

  // Start Bluetooth server
  Serial.print("Starting Bluetooth Server");
  SerialBT.begin("SensorDataServer");

  // Set built in LED as output
  pinMode(LED_BUILTIN, OUTPUT);
}

bool guiDisplayFlip = true;
void loop(){
  
  // Log
  if (guiDisplayFlip) {
    Serial.println("Checking for client");
    guiDisplayFlip = false;
  }
  
  // Check for new client
  if (SerialBT.available()) {
    String req = SerialBT.read();
    
    // Log
    Serial.println("New Client.");
    SetLEDHigh();

    // Add received time to
    //  response
    String response = String(millis(), DEC);
    response += " ";
          
    // Send unencrypted data back
    if (req.indexOf("GET /sensordata/CurrentTime") >= 0) {
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
    
    // Log
    Serial.println("Client disconnected.");
    Serial.println("");
    SetLEDLow();
  }
}
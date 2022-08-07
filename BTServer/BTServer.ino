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

// Timeout time
const long timeoutTime = 2000;

byte* btBuffer = (byte*)malloc(sizeof(byte) * INPUT_BUFFER_LIMIT);

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
  Serial.begin(BAUD_RATE);

  // Start Bluetooth server
  Serial.println("Starting bluetooth server");
  
  if (! SerialBT.begin(BT_SERVER_ID) ) {
    Serial.println("Failed to start bluetooth server");
    abort();
  }

  // Set built in LED as output
  pinMode(LED_BUILTIN, OUTPUT);

  SetLEDHigh();
}

bool guiDisplayFlip = true;
void loop(){

  // Log
  if (guiDisplayFlip) {
    Serial.println("Checking for client");
    guiDisplayFlip = false;
  }

  // Check for a message
  String req = GetPacket();
//  int i = 0;
//  while (SerialBT.available()) {
//    if (i > INPUT_BUFFER_LIMIT)
//      break;
//
//    byte btSerial = SerialBT.read();
//
//    btBuffer[i++] = btSerial;
//  }
//  btBuffer[i] = 0x00;

  // No message was waiting
//  if (i == 0)
//    return;

  // Flip the gui display back
  guiDisplayFlip = true;
  SetLEDLow();

  // Convert to arduino string
  //String req = (const char*)btBuffer;

  // Log
  Serial.println("New request: " + req);
  SetLEDHigh();

  // Add received time to
  //  response
  String response = String(millis(), DEC) + " ";
  
  // Send unencrypted data back
  if (req.indexOf("CurrentTime") >= 0) {
    Serial.println("Get current server time");
    response += "TimeRequest";

  } else if (req.indexOf("None") >= 0) {
    Serial.println("Get Unencrypted data");
    response += "Unencrypted Data";

  // Send aes encrypted data back
  } else if (req.indexOf("AES") >= 0) { 
    Serial.println("Get AES encrypted data");
    uint16_t len = encryptToCipherText((char*)clearText, 18, aes_iv);
    response += (const char*)cipherText;
    
  // Send des data back
  } else if (req.indexOf("DES") >= 0) { 
    Serial.println("Get DES encrypted data");
    response += "DES Enc Data";

  // Send des data back
  } else if (req.indexOf("ECC") >= 0) { 
    Serial.println("Get ECC encrypted data");
    response += "ECC Enc Data";
 
  } else {
    Serial.println("Not recognized: " + req);
    response += "NR: " + req;
  }

  response += " " + String(millis(), DEC);
  SendPacket(response);
  
  // Log
  Serial.println("Client disconnected.");
  SetLEDHigh();

}

String GetPacket() {
  while (!SerialBT.available()) {
    
  }
  
  // Read into buffer
  int i = 0;
  bool endFeed = false;
  while (!endFeed) {
    if (i > INPUT_BUFFER_LIMIT - 2)
      break;

    if (!SerialBT.available())
      continue;
      
    char btSerial = SerialBT.read();

    if ((const uint8_t)btSerial == (const uint8_t)0)
      endFeed = true;
      
    btBuffer[i++] = btSerial;
  }
  btBuffer[i] = 0x0;

  return (const char*)btBuffer;
}

void SendPacket(String msg) {
  msg.trim();
  
Serial.println("Sending via bt: " + msg);
  const uint8_t* src = (const uint8_t *)msg.c_str();
Serial.println("SIZEOF(src) = " + String(msg.length()));
  for (int i = 0; i < msg.length(); i++) {
    SerialBT.write(src[i]);
  }
  SerialBT.write((uint8_t)0);
}

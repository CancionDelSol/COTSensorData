/*
 * Bluetooth server for ESP32 module
 * Feeds back data similar to the Wifi module
 */

#include "BluetoothSerial.h"
#include "COTStd.h"
#include "AESLib.h"
#include "tinyECC.h"

#include <DES.h>

/*
 * From online resource: https://randomnerdtutorials.com/esp32-bluetooth-classic-arduino-ide/ 
 */
#if !defined(CONFIG_BT_ENABLED) || !defined(CONFIG_BLUEDROID_ENABLED)
#error Bluetooth is not enabled! Please run `make menuconfig` to and enable it
#endif

BluetoothSerial SerialBT;

// Timeout time
const long timeoutTime = 2000;

// Buffer for AES encryption
byte* btBuffer = (byte*)malloc(sizeof(byte) * INPUT_BUFFER_LIMIT);

void setup() {
  // Place the read buffer into clear text
  //  for AES encryption
  placeIntoClearText();

  // Initialize encryption library
  aes_init();

  // Begin serial communication
  Serial.begin(BAUD_RATE);

  // Start Bluetooth server
  Serial.println("Starting bluetooth server");
  
  if (!SerialBT.begin(BT_SERVER_ID) ) {
    Serial.println("Failed to start bluetooth server");
    abort();
  }

  // Set built in LED as output
  pinMode(LED_BUILTIN, OUTPUT);

  // Notify OK state
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

  // Flip the gui display back
  guiDisplayFlip = true;
  SetLEDLow();

  // Log
  Serial.println("New request: " + req);

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
    _desLib.encrypt(_desOut, _desIn, _desKey);
    response += "DES Enc Data";

  // Send des data back
  } else if (req.indexOf("ECC") >= 0) { 
    Serial.println("Get ECC encrypted data");

    // Encrypt using elliptic curve cryptography
    tinyECC tE;
    tE.plaintext = "ECC encrypted data";
    tE.encrypt();
    
    response += tE.ciphertext;
 
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
  
  const uint8_t* src = (const uint8_t *)msg.c_str();
  
  for (int i = 0; i < msg.length(); i++) {
    SerialBT.write(src[i]);
  }
  SerialBT.write((uint8_t)0);
}

/*
 * Bluetooth server for ESP32 module
 * Feeds back data similar to the Wifi module
 */

#include "BluetoothSerial.h"
#include "COTStd.h"
#include "AESLib.h"
#include "tinyECC.h"

/*
 * From online resource: https://randomnerdtutorials.com/esp32-bluetooth-classic-arduino-ide/ 
 */
#if !defined(CONFIG_BT_ENABLED) || !defined(CONFIG_BLUEDROID_ENABLED)
#error Bluetooth is not enabled! Please run `make menuconfig` to and enable it
#endif

BluetoothSerial SerialBT;

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
  delay(1500);

  // Initialize encryption library
  aes_init();

  // Begin serial communication
  Serial.begin(BAUD_RATE);

  // Start Bluetooth server
  Serial.println("Starting bluetooth server");
  SerialBT.begin(BT_SERVER_ID, false);

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

  // Check for a message
  int i = 0;
  bool endRead = false;
  int timeout = INT_MAX;
  while (!endRead) {
    if (!SerialBT.available()) {
      if (millis() > timeout)
        break;
      else
        continue;
    }

    timeout = millis() + 3000;
     
    Serial.println("Reading");
    
    if (i > INPUT_BUFFER_LIMIT)
      break;

    byte btSerial = SerialBT.read();

    btBuffer[i] = btSerial;
    btBuffer[i + 1] = 0x00;
    
    if (btBuffer[i++] == '\0') 
      break;
  }
  Serial.println("Out of read");
  
  btBuffer[i] = 0x00;

  // No message was waiting
  if (i == 0)
    return;

  Serial.println("We got a message");
  // Flip the gui display back
  guiDisplayFlip = true;

  // Convert to arduino string
  String req = (const char*)btBuffer;
  req.trim();

  // Log
  Serial.println("New request.");

  // Add received time to
  //  response
  String response = String(millis(), DEC);
  response += " ";
 
  // Send unencrypted data back
  if (req.indexOf("CurrentTime") >= 0) {
    Serial.println("Get current server time");
    response += "Time-Request";

  } else if (req.indexOf("None") >= 0) {
    Serial.println("Get unencrypted data");
    response += "Unencrypted-Data";

  // Send aes encrypted data back
  } else if (req.indexOf("AES") >= 0) { 
    Serial.println("Get AES encrypted data");

    uint16_t len = encryptToCipherText((char*)clearText, 18, aes_iv);

  // Send des data back
  } else if (req.indexOf("DES") >= 0) { 
    
    _desLib.encrypt(_desOut, _desIn, _desKey);
    char chars[9];

    std::memcpy(chars, _desOut, 8);
    chars[8] = '\0';
    String part = String(chars, HEX);
    Serial.println("Get-DES-encrypted-data: " + part);
    response += part;

  // Send des data back
  } else if (req.indexOf("ECC") >= 0) { 
    Serial.println("Get ECC encrypted data");
    // Encrypt using elliptic curve cryptography
    tinyECC tE;
    tE.plaintext = "ECC-encrypted-text";
    tE.encrypt();
    
    response += tE.ciphertext;
 
  } else {
    Serial.println("Not recognized: " + req);
    response += "Not-recognized:" + req;
  }

  response += " ";
  response += String(millis(), DEC);

  Serial.println("Sending back: " + response);
  SendPacket(response);
  
  // Log
  Serial.println("Client disconnected.");

}

void SendPacket(String msg) {
  msg.trim();
  
  const uint8_t* src = (const uint8_t *)msg.c_str();
  for (int i = 0; i < msg.length(); i++) {
    if (src[i] == 0x00) 
      continue;
      
    SerialBT.write(src[i]);
  }
  SerialBT.write((uint8_t)0);
  SerialBT.flush();
}
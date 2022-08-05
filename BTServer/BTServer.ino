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
  Serial.print("Starting bluetooth server");
  SerialBT.begin(BT_SERVER_ID, true);

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
  int i = 0;
  while (SerialBT.available()) {
    if (i > INPUT_BUFFER_LIMIT)
      break;

    byte btSerial = SerialBT.read();

    btBuffer[i++] = btSerial;
  }
  btBuffer[i] = 0x00;

  // No message was waiting
  if (i == 0)
    return;

  // Flip the gui display back
  guiDisplayFlip = true;
  SetLEDLow();

  // Convert to arduino string
  String req = (const char*)btBuffer;

  // Log
  Serial.println("New request.");
  SetLEDHigh();

  // Add received time to
  //  response
  String response = String(millis(), DEC);
  response += " ";
 
  // Send unencrypted data back
  if (req.indexOf("CurrentTime") >= 0) {
    Serial.println("Get current server time");
    response += "Time Request";

  } else if (req.indexOf("None") >= 0) {
    Serial.println("Get unencrypted data");
    response += "Unencrypted Data";

  // Send aes encrypted data back
  } else if (req.indexOf("AES") >= 0) { 
    Serial.println("Get AES encrypted data");

    uint16_t len = encryptToCipherText((char*)clearText, 18, aes_iv);

  // Send des data back
  } else if (req.indexOf("DES") >= 0) { 
    Serial.println("Get DES encrypted data");
    response += "DES Encrypted Data";

  // Send des data back
  } else if (req.indexOf("ECC") >= 0) { 
    Serial.println("Get ECC encrypted data");
    response += "ECC Encrypted Data";
 
  } else {
    Serial.println("Not recognized: " + req);
    response += "Not recognized: " + req;
  }

  response += " ";
  response += String(millis(), DEC);
 
  SerialBT.write((const uint8_t *)response.c_str(), sizeof(response));
  SerialBT.flush();
  
  // Log
  Serial.println("Client disconnected.");
  Serial.println("");
  SetLEDHigh();

}
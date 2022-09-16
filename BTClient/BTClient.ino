/*
 * Bluetooth client for ESP32 module
 */

#include "BluetoothSerial.h"
#include "COTStd.h"
#include "AESLib.h"
#include "tinyECC.h"

// AES Decryption support
byte dec_iv[N_BLOCK] = { 0, 0, 0, 0,
                         0, 0, 0, 0,
                         0, 0, 0, 0,
                         0, 0, 0, 0 };

/*
 * From online resource: https://randomnerdtutorials.com/esp32-bluetooth-classic-arduino-ide/ 
 */
#if !defined(CONFIG_BT_ENABLED) || !defined(CONFIG_BLUEDROID_ENABLED)
#error Bluetooth is not enabled! Please run `make menuconfig` to and enable it
#endif

BluetoothSerial SerialBT;

bool isConnected = false;

void setup() {
  // General initialization
  GenInit();
  
  // Initialize SerialBT
  SerialBT.begin(BT_CLIENT_ID, true);

  // Attempt to connect
  bool connected = SerialBT.connect(BT_SERVER_ID);

  if (connected) {
    Serial.println("Connected Successfully");
    SetLEDHigh();
  } else {
    while (!SerialBT.connected(10000)) {
      Serial.println("Failed to connect");
      break;
    }
  }

}

void loop() {
  // Read serial and make
  //  appropriate request
  String req = "";
  bool hasRequest = false;
  if (Serial.available() > 0) {
    //Serial.println("Reading from Serial");
    req = Serial.readString();
    //Serial.println("Read: " + req);
    hasRequest = true;
  }

  if (!hasRequest) {
    return;
  }

  SetLEDLow();

  // Make raw data request
  //  index will be the offset
  //  for encryption type
  String startTime = String(millis(), DEC);
  String resp = GetDataFromSensorProvider(req);
  resp.trim();
  String endTime = String(millis(), DEC);

  // Communicate back response
  SendMsgSerial(startTime + COMM_DELIM + resp + COMM_DELIM + endTime);

  // Set LED high for OK status
  SetLEDHigh();
  
}

// Receive each piece individually:
//  TimeStampOne
//  Data (Up to Eight packets)
//  TimeStampTwo
String GetDataFromSensorProvider(String request) {
  SendBluetoothPacket(request);

  String resp = GetBluetoothPacket();

  int partSize = seperate(resp, sPtr, 3, COMM_DELIM);

  if (partSize < 3) {
    return resp;
  }

  if (request.indexOf("DES") >= 0) {
    CopyToDESIn(sPtr[1]);
    _desLib.decrypt(_desOut, _desIn, _desKey);
    char out[9];
    std::memcpy(out, _desOut, 8);
    out[8] = '\0';
    String part = String(out, DEC);
    std::strcpy(sPtr[1], part.c_str());

  } else if (request.indexOf("AES") >= 0) {
    // Get the input
    String input = sPtr[1];

    char buffer[512];
    sprintf(buffer, "%s", input.c_str()); 
    uint16_t clen = input.length();
    
    String output = decryptToClearText(buffer, input.length(), aes_iv);

    for (int i = 0; i < 16; i++) {
      dec_iv[i] = 0;
    }
    std::strcpy(sPtr[1], output.c_str());
    
  } else if (request.indexOf("ECC") >= 0) {
    // Do nothing
  }

  String rVal = "";
  for (int i = 0; i < 3; i++) {
    rVal += sPtr[i];
    rVal += COMM_DELIM;
  }

  return rVal;
}

// Recieve bluetooth packet
String GetBluetoothPacket() {
  // Read into buffer
  int i = 0;
  bool endFeed = false;
  int timeout = millis() + 15000;
  while (!endFeed) {
    if (!SerialBT.available()) {
      if (millis() > timeout)
        break;
      else 
        continue;
    }

    timeout = millis() + 3000;

    if (i > BLUE_INPUT_BUFFER_SIZE)
      break;
      
    byte btSerial = SerialBT.read();

    btBuffer[i] = btSerial;
    btBuffer[i + 1] = 0x00;
    
    if (btBuffer[i++] == '\0') 
      break;
  }

  return (const char*)btBuffer;
}

// Send bluetooth packet
void SendBluetoothPacket(String msg) {
  msg.trim();
  
  const uint8_t* src = (const uint8_t *)msg.c_str();
  for (int i = 0; i < msg.length(); i++) {
    SerialBT.write(src[i]);
  }
  SerialBT.write((uint8_t)0);
  SerialBT.flush();
}
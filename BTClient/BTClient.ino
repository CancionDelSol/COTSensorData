/*
 * Bluetooth client for ESP32 module
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

bool isConnected = false;

byte* btBuffer = (byte*)malloc(sizeof(byte) * INPUT_BUFFER_LIMIT);

void setup() {
  // Set Built-In LED as output
  pinMode(LED_BUILTIN, OUTPUT);
  
  Serial.begin(BAUD_RATE);

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
  SendMsgSerial(startTime + " " + resp + " " + endTime);

  // Set LED high for OK status
  SetLEDHigh();
  
}

// Receive each piece individually:
//  TimeStampOne
//  Data (Up to Eight packets)
//  TimeStampTwo
String GetDataFromSensorProvider(String request) {
  SendPacket(request);

  String resp = GetPacket();

  int partSize = seperate(resp, sPtr, 3);

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
    // Copy into byte array
    std::memcpy(cipherText, sPtr[1].c_str(), input.length());

    // Decrypt
    uint16_t decLen = decryptToClearText(cipherText, 2*INPUT_BUFFER_LIMIT, aes_iv);
    
  } else if (request.indexOf("ECC") >= 0) {
    tinyECC tE;
    char buff[128];
    buff[0] = '\0';
    int buffIndex = 0;
    for (int i = 0; i < 32; i++) {
      String suff = String((uint8_t)sPtr[1][i]);
      snprintf(buff, 128, "%s%s%s", buff, suff, ",");
    }
    
    tE.ciphertext = String(buff);
    tE.decrypt();

    std::strcpy(sPtr[1], tE.plaintext.c_str());
  }



  String rVal = "";
  for (int i = 0; i < 3; i++) {
    rVal += sPtr[i];
    rVal += " ";
  }

  return rVal;
}

String GetPacket() {
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

    if (i > INPUT_BUFFER_LIMIT)
      break;
      
    byte btSerial = SerialBT.read();

    btBuffer[i] = btSerial;
    btBuffer[i + 1] = 0x00;
    
    if (btBuffer[i++] == '\0') 
      break;
  }

  return (const char*)btBuffer;
}

void SendPacket(String msg) {
  msg.trim();
  
  const uint8_t* src = (const uint8_t *)msg.c_str();
  for (int i = 0; i < msg.length(); i++) {
    SerialBT.write(src[i]);
  }
  SerialBT.write((uint8_t)0);
  SerialBT.flush();
}

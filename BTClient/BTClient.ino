/*
 * Bluetooth client for ESP32 module
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
  } else {
    while (!SerialBT.connected(10000)) {
      Serial.println("Failed to connect");
      break;
    }
  }

  SetLEDHigh();
}

void loop() {
  // Read serial and make
  //  appropriate request
  String req = "";
  bool hasRequest = false;
  if (Serial.available() > 0) {
    req = Serial.readString();
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

  return resp;
}

String GetPacket() {
  while (!SerialBT.available()) {
    // Intentionally left empty
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

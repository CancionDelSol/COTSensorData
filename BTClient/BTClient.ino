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

  SerialBT.begin(BT_CLIENT_ID, false);

  // Attempt to connect
  SerialBT.connect(BT_SERVER_ID);

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

  SetLEDHigh();
  
}

String GetDataFromSensorProvider(String request) {
  SerialBT.write((const uint8_t *)request.c_str(), sizeof(request));

  while (!SerialBT.available()) { }

  // Read into buffer
  int i = 0;
  while (SerialBT.available()) {
    if (i > INPUT_BUFFER_LIMIT)
      break;

    byte btSerial = SerialBT.read();

    btBuffer[i++] = btSerial;
  }
  btBuffer[i] = 0x00;

  return (const char*)btBuffer;
}

void ConnectToBTServer() {
  if (SerialBT.isReady())
    return;
    
  isConnected = false;

  SerialBT.connect(BT_SERVER_ID);
  
  isConnected = SerialBT.connected(5000);
}

void SendMsgSerial(String msg) {
  Serial.print("<" + msg + ">");
}
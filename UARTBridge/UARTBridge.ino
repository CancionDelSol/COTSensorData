#include <SoftwareSerial.h>
#include "COTStd.h"
#include <stdio.h>

#define RX_PIN 16
#define TX_PIN 17

SoftwareSerial softSerial(RX_PIN, TX_PIN);

void setup() {
  GenInit();
  Serial.println("Starting up");
  softSerial.begin(38400);

  softSerial.enableRx(true);
}

void loop() {

  CheckMsgFromUART();

  CheckMsgFromUSB();

  delay(3);
}

void CheckMsgFromUART() {
  char buff[512] = { 0 };
  int readCount = softSerial.read(buff, 512);

  if (readCount > 0) {
    SetLEDHigh();
    Serial.print(buff);
    SetLEDLow();
  }
}

void CheckMsgFromUSB() {
  // Read serial and make
  //  appropriate request
  String req = "";
  bool hasRequest = false;
  if (Serial.available() > 0) {
    //Serial.println("Reading from Serial");
    req = Serial.readString();

    hasRequest = true;
  }

  if (!hasRequest)
    return;
    
  SetLEDHigh();
  softSerial.write(req.c_str(), req.length());
  SetLEDLow();
}
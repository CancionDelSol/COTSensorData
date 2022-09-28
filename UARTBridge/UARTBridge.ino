#include <SoftwareSerial.h>
#include "COTStd.h"
#include <stdio.h>

#define RX_PIN 16
#define TX_PIN 17

SoftwareSerial softSerial(RX_PIN, TX_PIN);

volatile bool isReading = false;
void setup() {
  GenInit();

  softSerial.begin(38400);

  softSerial.enableRx(true);
}

void loop() {
  if (!isReading)
    CheckMsgFromUART();

  CheckMsgFromUSB();

  delay(3);
}

void CheckMsgFromUART() {
  isReading = true;

  char buff[16] = { 0 };
  int readCount = softSerial.read(buff, 16);

  if (readCount > 0) {
    Serial.print(buff);
  }
  
  isReading = false;
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

  softSerial.write(req.c_str(), req.length());
}
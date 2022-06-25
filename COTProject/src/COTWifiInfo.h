#ifndef COT_WIFI_INFO
#define COT_WIFI_INFO

// Mandatory includes
#include <Arduino.h>

// Wifi Credentials
const char* SSID = "ESP_9D048D";
const char* PWD = "";

// Built in LED pinout for
// ESP32 Module bought off
// of Amazon
const int LED_BUILTIN = 2;

// Set baud rate for Serial Communication
const int BAUD_RATE = 115200;

// Helper functions for setting
//  built in LED high and low
void SetLEDHigh() {
  digitalWrite(LED_BUILTIN, HIGH);
}
void SetLEDLow() {
  digitalWrite(LED_BUILTIN, LOW);
}

#endif


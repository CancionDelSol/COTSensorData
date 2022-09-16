#ifndef COT_STD
#define COT_STD

#define BAUD 115200
#define BT_SERVER_ID "SensorDataServer"
#define BT_CLIENT_ID "ESPBluetoothClient"

// Mandatory includes
#include <Arduino.h>
#include <DES.h>
#include "AESLib.h"
#include <stdlib.h>

#include <iostream>
#include <cstddef>
#include <cstring>
#include <vector>

// Wifi Credentials
const char* SSID = "ESP_9D048D";
const char* PWD = "";

// Built in LED pinout for
// ESP32 Module bought off
// of Amazon
const int LED_BUILTIN = 2;

// Set baud rate for Serial Communication
const int BAUD_RATE = 115200;

/* Serial output */
void SendMsgSerial(String msg) {
  Serial.print("<" + msg + ">");
}

/* String splitting */
#define COMM_DELIM " "
char *sPtr[3];
char s[128];
int seperate(String str, char **p, int size, const char* delim) {
  int n;

  std::strcpy(s, str.c_str());

  *p++ = std::strtok(s, delim);
  for (n = 1; NULL != (*p++ = std::strtok(NULL, delim)); n++) {
    if (size == n)
      break;
  }

  return n;
}
int seperate(String str, char **p, int size) {
  return seperate(str, p, size, " ");
}


/* LED Controls */
void SetLEDHigh() {
  digitalWrite(LED_BUILTIN, HIGH);
}
void SetLEDLow() {
  digitalWrite(LED_BUILTIN, LOW);
}

/*
 * AES encryption support
 * Pulled from example under
 *  the github repo -> https://github.com/suculent/thinx-aes-lib.git
 */
AESLib _aesLib;

#define DES_BUFFER_LIMIT 16
unsigned char readBuffer[DES_BUFFER_LIMIT] = "DEADBEEF";

byte aes_key[] =   { 0x53, 0x43, 0x60, 0xBE,
                     0x1A, 0xAA, 0x72, 0xB1,
                     0x97, 0x23, 0xC1, 0xD2,
                     0x7A, 0x01, 0x23, 0xC4 };

byte aes_iv[N_BLOCK] = { 0xA1, 0xB0, 0x0B, 0x1A, 
                         0xC1, 0xA2, 0x2A, 0x1C,
                         0xC9, 0xA3, 0x3A, 0x9C,
                         0xA4, 0xC4, 0x4C, 0x4A };

// Encrypt message
String encryptToCipherText(char* msg, uint16_t msgLen, byte iv[]) {
  int cipherlength = _aesLib.get_cipher64_length(msgLen);

  char encrypted[cipherlength];
  _aesLib.encrypt64(msg, msgLen, encrypted, aes_key, sizeof(aes_key), iv);
  
  // Return the cipher length
  return String(encrypted);
}

// Decrypt message
String decryptToClearText(char* msg, uint16_t msgLen, byte iv[]) {
  char decrypted[msgLen];
  _aesLib.decrypt64(msg, msgLen, decrypted, aes_key, sizeof(aes_key), iv);
  return decrypted;
}

// Initialize AES
void aes_init() {
  _aesLib.gen_iv(aes_iv);
  _aesLib.set_paddingmode(paddingMode::CMS);
}

/*
 * DES Encryption support
 */
DES _desLib;
byte _desOut[8];
byte _desIn[] = { 0x44, 0x45, 0x41, 0x44, 0x42, 0x45, 0x45, 0x46 };
byte _desKey[] = { 0x3b, 0x38, 0x98, 0x37, 0x15, 0x20, 0xf7, 0x5e };

void CopyToDESIn(std::string input) {
  std::memcpy(_desIn, input.c_str(), input.length());
  //std::strcpy((char*)_desIn, input.c_str());
}

/*
 * BLE Support
 */

// UUIDs 
#define BLE_SERVICE_UUID        "4fafc201-1fb5-459e-8fcc-c5c9c331914b"
#define CHARACTERISTIC_UUID "beb5483e-36e1-4688-b7f5-ea07361b26a8"

/*
 * Bluetooth Support
 */
#define BT_TIMEOUT 5000
#define BLUE_INPUT_BUFFER_SIZE 512

// Buffer used for communication
byte* btBuffer = (byte*)malloc(sizeof(byte) * BLUE_INPUT_BUFFER_SIZE);

/*
 * All boards
 */
void GenInit() {
  // Initialize AES Library
  aes_init();

  std::srand(0);

  // Set Built-In LED as output
  pinMode(LED_BUILTIN, OUTPUT);

  // Serial
  Serial.begin(BAUD_RATE);
  while(!Serial);
}

#endif
  
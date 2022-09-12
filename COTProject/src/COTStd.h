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
char *sPtr[3];
char s[128];
int seperate(String str, char **p, int size) {
  int n;

  std::strcpy(s, str.c_str());

  *p++ = std::strtok(s, " ");
  for (n = 1; NULL != (*p++ = std::strtok(NULL, " ")); n++) {
    if (size == n)
      break;
  }

  return n;
}

/* LED Controls */
void SetLEDHigh() {
  digitalWrite(LED_BUILTIN, HIGH);
}
void SetLEDLow() {
  digitalWrite(LED_BUILTIN, LOW);
}

///*
// * AES encryption support
// * Pulled from example under
// *  the github repo -> https://github.com/suculent/thinx-aes-lib.git
// */
#define INPUT_BUFFER_LIMIT (64 + 1)
#define BT_TIMEOUT 5000

unsigned char clearText[INPUT_BUFFER_LIMIT] = {0}; // THIS IS INPUT BUFFER (FOR TEXT)
unsigned char cipherText[2*INPUT_BUFFER_LIMIT] = {0}; // THIS IS OUTPUT BUFFER (FOR BASE64-ENCODED ENCRYPTED DATA)
unsigned char readBuffer[18] = "AES Enc Data";

/*
 * AES encryption support
 * Pulled from example under
 *  the github repo -> https://github.com/suculent/thinx-aes-lib.git
 */
AESLib _aesLib;
byte aes_key[]       = { 0x6D, 0x12, 0xF7, 0x09,
                         0x3C, 0xAB, 0x88, 0xCF,
                         0xAB, 0xF7, 0x15, 0xBC,
                         0x09, 0x1F, 0x00, 0xAA };

byte aes_iv[N_BLOCK] = { 0x0A, 0x0B, 0x0C, 0x0D,
                         0x0C, 0x0D, 0x0E, 0x10,
                         0x11, 0x12, 0x13, 0x14,
                         0x15, 0x16, 0x17, 0x18 };

/*
 * Method to encrypt character pointer (text)
 *  to cipher text
 */
uint16_t encryptToCipherText(char* msg, uint16_t msgLen, byte iv[]) {
  // Log to serial client
  Serial.println("Calling encrypt (string)...");

  // Encrypt the text in the pointer's
  //  location and place into byt array
  int cipherlength =_aesLib.encrypt((byte*)msg, msgLen, (char*)cipherText, aes_key, sizeof(aes_key), iv);
  
  // Return the cipher length
  return cipherlength;
}

/*
 * Decrypt byte array into 
 */
uint16_t decryptToClearText(byte msg[], uint16_t msgLen, byte iv[]) {
  // Log to serial client
  Serial.print("Calling decrypt... ");

  // Do the decryption and place output into
  //  
  uint16_t dec_bytes =_aesLib.decrypt(msg, msgLen, (char*)clearText, aes_key, sizeof(aes_key), iv);
  Serial.print("Decrypted bytes: "); Serial.println(dec_bytes);
  return dec_bytes;
}

void placeIntoClearText() {
  // Copy text in the readBuffer
  //  into the character array used
  //  for AES encryption
  sprintf((char*)clearText, "%s", readBuffer);
}

// Generate IV (once)
void aes_init() {
  _aesLib.gen_iv(aes_iv);
  _aesLib.set_paddingmode((paddingMode)0);
}

/*
 * DES Encryption support
 */
DES _desLib;
byte _desOut[8];
//byte _desOut[] = { 0x44, 0x45, 0x41, 0x44, 0x42, 0x45, 0x45, 0x46 };
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

#endif


/*
    Based on Neil Kolban example for IDF: https://github.com/nkolban/esp32-snippets/blob/master/cpp_utils/tests/BLE%20Tests/SampleServer.cpp
    Ported to Arduino ESP32 by Evandro Copercini
    updates by chegewara
*/

#include <BLEDevice.h>
#include <BLEUtils.h>
#include <BLEServer.h>
#include "AESLib.h"
#include "tinyECC.h"

#include <DES.h>

#include "COTStd.h"

// Save a characteristic
BLECharacteristic *pCharacteristic;

// Server callbacks
bool deviceConnected = false;
class MyServerCallbacks: public BLEServerCallbacks {
    void onConnect(BLEServer* pServer) {
      deviceConnected = true;
    };

    void onDisconnect(BLEServer* pServer) {
      deviceConnected = false;
    }
};

void setup() {
  // Place read buffer into clear text
  placeIntoClearText();

  // Initialize encryption library
  aes_init();

  // Begin serial communication
  Serial.begin(BAUD_RATE);

  // Set up BLE Service
  Serial.println("Starting BLE work!");
  BLEDevice::init("ESP32BLE");
  BLEServer *pServer = BLEDevice::createServer();
  pServer->setCallbacks(new MyServerCallbacks());

  // Create the BLE Service
  BLEService *pService = pServer->createService(BLE_SERVICE_UUID);

  /* Multiple characteristics */

  // Charactercteristic
  pCharacteristic = pService->createCharacteristic(
                      CHARACTERISTIC_UUID,
                      BLECharacteristic::PROPERTY_READ |
                      BLECharacteristic::PROPERTY_WRITE |
                      BLECharacteristic::PROPERTY_NOTIFY |
                      BLECharacteristic::PROPERTY_INDICATE
                    );

  pCharacteristic->setValue("Write your request here");
  pService->start();
  
  BLEAdvertising *pAdvertising = BLEDevice::getAdvertising();
  pAdvertising->addServiceUUID(BLE_SERVICE_UUID);
  pAdvertising->setScanResponse(true);

  pAdvertising->setMinPreferred(0x06);  // functions that help with iPhone connections issue
  pAdvertising->setMinPreferred(0x12);
  
  BLEDevice::startAdvertising();
  Serial.println("Device is advertised");
}

void loop() {
  // Check the characteristic to see which
  //  encryption is requested and update
  //  the characteristic accordingly

  if (deviceConnected) {
    // Check the characteristic value for a request
    String req = String(pCharacteristic->getValue().c_str());

    // Add received time to
    //  response
    String response = String(millis(), DEC) + " ";

    // Send unencrypted data back
    if (req.indexOf("CurrentTime") >= 0) {
      Serial.println("Get current server time");
      response += "TimeRequest";

    } else if (req.indexOf("None") >= 0) {
      Serial.println("Get Unencrypted data");
      response += "Unencrypted Data";

    // Send aes encrypted data back
    } else if (req.indexOf("AES") >= 0) { 
      Serial.println("Get AES encrypted data");
      uint16_t len = encryptToCipherText((char*)clearText, 18, aes_iv);
      response += (const char*)cipherText;
      
    // Send des data back
    } else if (req.indexOf("DES") >= 0) { 
      Serial.println("Get DES encrypted data");
      _desLib.encrypt(_desOut, _desIn, _desKey);
      response += "DES Enc Data";

    // Send des data back
    } else if (req.indexOf("ECC") >= 0) { 
      Serial.println("Get ECC encrypted data");

      // Encrypt using elliptic curve cryptography
      tinyECC tE;
      tE.plaintext = "ECC encrypted data";
      tE.encrypt();
      
      response += tE.ciphertext;
  
    } else {
      // There has been no request
      return;
    }

    response += " " + String(millis(), DEC);

    pCharacteristic->setValue(response.c_str());
  }
}

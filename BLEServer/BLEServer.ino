/*
    Based on Neil Kolban example for IDF: https://github.com/nkolban/esp32-snippets/blob/master/cpp_utils/tests/BLE%20Tests/SampleWrite.cpp
    Ported to Arduino ESP32 by Evandro Copercini
*/

#include <BLEDevice.h>
#include <BLEUtils.h>
#include <BLEServer.h>
#include "COTStd.h"
#include "tinyECC.h"

// AES Encryption support
byte enc_iv[N_BLOCK] = { 0, 0, 0, 0,
                         0, 0, 0, 0,
                         0, 0, 0, 0,
                         0, 0, 0, 0 };

// Variables
bool deviceConnected = false;
bool oldDeviceConnected = false;
BLEServer* pServer = NULL;
BLECharacteristic* pCharacteristic = NULL;

// Callback for writing to characteristic
class MyCallbacks: public BLECharacteristicCallbacks {

    // Read the characteristic value
    //  and encrypt the phrase according
    //  to the request
    void onWrite(BLECharacteristic *pCharacteristic) {
      std::string value = pCharacteristic->getValue();

      if (value.length() > 0) {

        String req = String(value.c_str());

        // Add receive time to
        //  response
        String response = String(millis(), DEC);
        response += COMM_DELIM;
       
        // Send unencrypted data back
        if (req.indexOf("CurrentTime") >= 0) {
          Serial.println("Get current server time");
          response += "Time-Request";
      
        } else if (req.indexOf("None") >= 0) {
          Serial.println("Get unencrypted data");
          response += "DEADBEEF";
      
        // Send aes encrypted data back
        } else if (req.indexOf("AES") >= 0) { 
          Serial.println("Get AES encrypted data");
      
          String input = "DEADBEEF";
          char buffer[512];
          sprintf(buffer, "%s", input);
          
          String output = encryptToCipherText(buffer, String(buffer).length(), enc_iv);
      
          // Clear the encryption
          //  initialization vector
          for (int i = 0; i < 16; i++) {
            enc_iv[i] = 0;
          }
      
          // Append response
          response += output;
      
        // Send des data back
        } else if (req.indexOf("DES") >= 0) {
          
          _desLib.encrypt(_desOut, _desIn, _desKey);
          char chars[9];
      
          std::memcpy(chars, _desOut, 8);
          chars[8] = '\0';
          String part = String(chars);
          Serial.println("Get-DES-encrypted-data: " + part);
          response += part;
      
        // Send des data back
        } else if (req.indexOf("ECC") >= 0) { 
          Serial.println("Get-ECC-encrypted-data");
      
          // Encrypt using elliptic curve cryptography
          tinyECC tE;
          tE.plaintext = "DEADBEEF";
          tE.encrypt();
      
          tE.genSig();
      
          tE.verifySig();
          tE.decrypt();
          
          //response += String(tE.Sig[0])+"!"+String(tE.Sig[1])+"!";
          response += tE.plaintext;
          
        } else {
          Serial.println("Not recognized: " + req);
          response += "Not-recognized:" + req;
        }
      
        response += COMM_DELIM;
        response += String(millis(), DEC);
        response.trim();

        pCharacteristic->setValue(response.c_str());
        pCharacteristic->notify();
      }
    }
};

// Callback for connect/disconnect
class MyServerCallbacks: public BLEServerCallbacks {
    void onConnect(BLEServer* pServer) {
      deviceConnected = true;
    };

    void onDisconnect(BLEServer* pServer) {
      deviceConnected = false;
    }
};

void setup() {
  GenInit();

  BLEDevice::init("MyESP32");
  
  pServer = BLEDevice::createServer();
  pServer->setCallbacks(new MyServerCallbacks());

  BLEService *pService = pServer->createService(BLE_SERVICE_UUID);

  pCharacteristic = pService->createCharacteristic(
                                         CHARACTERISTIC_UUID,
                                         BLECharacteristic::PROPERTY_READ   |
                                         BLECharacteristic::PROPERTY_WRITE  |
                                         BLECharacteristic::PROPERTY_NOTIFY |
                                         BLECharacteristic::PROPERTY_INDICATE
                                       );

  pCharacteristic->setCallbacks(new MyCallbacks());

  pCharacteristic->setValue("Hello World");
  pService->start();

  BLEAdvertising *pAdvertising = pServer->getAdvertising();
  pAdvertising->addServiceUUID(BLE_SERVICE_UUID);
  pAdvertising->setScanResponse(true);
  pAdvertising->setMinPreferred(0x06);  // functions that help with iPhone connections issue
  pAdvertising->setMinPreferred(0x12);
  BLEDevice::startAdvertising();
}

void loop() {
  if (deviceConnected) {
      //String val = "Testing: " + String(millis(), DEC);
      //pCharacteristic->setValue(val.c_str());
      //pCharacteristic->notify();
      delay(10);
  }
  // disconnecting
  if (!deviceConnected && oldDeviceConnected) {
      delay(500); // give the bluetooth stack the chance to get things ready
      pServer->startAdvertising(); // restart advertising
      Serial.println("start advertising");
      oldDeviceConnected = deviceConnected;
  }
  // connecting
  if (deviceConnected && !oldDeviceConnected) {
      // do stuff here on connecting
      oldDeviceConnected = deviceConnected;
  }
}

/**
 * A BLE client example that is rich in capabilities.
 * There is a lot new capabilities implemented.
 * author unknown
 * updated by chegewara
 */

#include <BLEDevice.h>
#include <BLEUtils.h>
#include <BLEServer.h>

#include "AESLib.h"
#include "tinyECC.h"

#include <DES.h>

#include "COTStd.h"

// The remote service we wish to connect to.
static BLEUUID serviceUUID("4fafc201-1fb5-459e-8fcc-c5c9c331914b");

// Hold the current request
//  added to, then cleared
//  by the pChar update 
//  callback
String response = "";

// Some toggles
static boolean doConnect = false;
static boolean connected = false;
static boolean doScan = false;

// The characteristics from the
//  BLE service
static BLERemoteCharacteristic* pRemChar;

// The advertised device that hosts
//  the service
static BLEAdvertisedDevice* myDevice;

static void notifyCallback(
  BLERemoteCharacteristic* pBLERemoteCharacteristic,
  uint8_t* pData,
  size_t length,
  bool isNotify) {
    
    // Get the characteristic text
    //  and feedback through serial
    //  output
    // String charUUID = pBLERemoteCharacteristic->getUUID().toString(); // .c_str()
    // char* buffer[length+1];
    // for (int i = 0; i < length; i++) {
    //   buffer[i] = (char)pData[i];
    // }
    // pData[length] = '\0';
    // String charVal = String(buffer);
    String charVal = String((char*)pData);

    // Get the end time
    String endTime = String(millis(), DEC);

    // Send back via serial
    SendMsgSerial(response + charVal + " " + endTime);
}

class MyClientCallback : public BLEClientCallbacks {
  void onConnect(BLEClient* pclient) {
  }

  void onDisconnect(BLEClient* pclient) {
    connected = false;
    Serial.println("onDisconnect");
  }
};

// Save the reference to the service
BLERemoteService* pRemoteService;

// Save the reference to the client
BLEClient*  pClient;

// Connect to the BLE server
bool connectToServer() {
    SetLEDHigh();
    Serial.print("Forming a connection to ");
    Serial.println(myDevice->getAddress().toString().c_str());
    
    pClient  = BLEDevice::createClient();
    Serial.println(" - Created client");

    pClient->setClientCallbacks(new MyClientCallback());

    // Connect to the remote BLE Server.
    pClient->connect(myDevice);  // if you pass BLEAdvertisedDevice instead of address, it will be recognized type of peer device address (public or private)
    Serial.println(" - Connected to server");
    pClient->setMTU(517); //set client to request maximum MTU from server (default is 23 otherwise)
  
    // Obtain a reference to the service we are after in the remote BLE server.
    pRemoteService = pClient->getService(serviceUUID);
    if (pRemoteService == nullptr) {
      Serial.print("Failed to find our service UUID: ");
      Serial.println(serviceUUID.toString().c_str());
      pClient->disconnect();
      return false;
    }
    Serial.println(" - Found our service");


    // Obtain a reference to the characteristic in the service of the remote BLE server.
    pRemChar = pRemoteService->getCharacteristic(CHARACTERISTIC_UUID);
    if (pRemChar == nullptr) {
      Serial.print("Failed to find our characteristic UUID: ");
      Serial.println(CHARACTERISTIC_UUID);
      pClient->disconnect();
      return false;
    }
    Serial.println(" - Found our characteristic");

    // Read the value of the characteristic.
    if(pRemChar->canRead()) {
      std::string value = pRemChar->readValue();
      Serial.print("The characteristic value was: ");
      Serial.println(value.c_str());
    }

    if(pRemChar->canNotify())
      pRemChar->registerForNotify(notifyCallback);

    SetLEDHigh();
    connected = true;
    return true;
}

/**
 * Scan for BLE servers and find the first one that advertises the service we are looking for.
 */
class MyAdvertisedDeviceCallbacks: public BLEAdvertisedDeviceCallbacks {
  // Called for each advertising BLE server.
  void onResult(BLEAdvertisedDevice advertisedDevice) {
    Serial.print("BLE Advertised Device found: ");
    Serial.println(advertisedDevice.toString().c_str());

    // We have found a device, let us now see if it contains the service we are looking for.
    if (advertisedDevice.haveServiceUUID() && advertisedDevice.isAdvertisingService(serviceUUID)) {

      BLEDevice::getScan()->stop();
      myDevice = new BLEAdvertisedDevice(advertisedDevice);
      doConnect = true;
      doScan = true;

    }
  }
};


void setup() {
  // Set Built-In LED as output
  pinMode(LED_BUILTIN, OUTPUT);
  
  Serial.begin(BAUD_RATE);
  
  Serial.println("Starting BLEDevice Client");
  BLEDevice::init("");

  // Retrieve a Scanner and set the callback we want to use to be informed when we
  // have detected a new device.  Specify that we want active scanning and start the
  // scan to run for 5 seconds.
  BLEScan* pBLEScan = BLEDevice::getScan();
  pBLEScan->setAdvertisedDeviceCallbacks(new MyAdvertisedDeviceCallbacks());
  pBLEScan->setInterval(1349);
  pBLEScan->setWindow(449);
  pBLEScan->setActiveScan(true);
  pBLEScan->start(5, false);
} // End of setup.

// This is the Arduino main loop function.
void loop() {

  // If the flag "doConnect" is true then we have scanned for and found the desired
  // BLE Server with which we wish to connect.  Now we connect to it.  Once we are 
  // connected we set the connected flag to be true.
  if (doConnect == true) {
    if (connectToServer()) {
      Serial.println("We are now connected to the BLE Server.");
    } else {
      Serial.println("We have failed to connect to the server; there is nothin more we will do.");
    }
    doConnect = false;
  }

  // If we are connected to a peer BLE Server, update the characteristic each time we are reached
  if (connected) {

    // Always have LED High
    //  when connected, unless
    //  in the process of a
    //  serial request
    SetLEDHigh();

    // Read serial and make
    //  appropriate request
    String req = "";
    bool hasRequest = false;
    if (Serial.available() > 0) {
      req = Serial.readString();
      hasRequest = true;
    }

    if (!hasRequest) {
      delay(20);
      return;
    }

    // Set low for process
    //  serial request
    SetLEDLow();

    // Initialize the response
    String startTime = String(millis(), DEC);
    response = String(startTime + " ");

    req.trim();

    // Set the characteristic's value
    //  to the requested encryption
    pRemChar->writeValue(req.c_str(), req.length());

  }else if(doScan){
    BLEDevice::getScan()->start(0);
  }
  
  delay(1000);
}
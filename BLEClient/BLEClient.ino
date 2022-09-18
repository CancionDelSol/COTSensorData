#include "BLEDevice.h"
#include "COTStd.h"

// Response builder
String startTime = "";
String lastRequest = "";

// AES Decryption support
byte dec_iv[N_BLOCK] = { 0, 0, 0, 0,
                         0, 0, 0, 0,
                         0, 0, 0, 0,
                         0, 0, 0, 0 };

// Remote service
static BLEUUID serviceUUID(BLE_SERVICE_UUID);

// Characteristic
static BLEUUID charUUID(CHARACTERISTIC_UUID);

// Runtime variables
static boolean doConnect = false;
static boolean connected = false;
static boolean doScan = false;

// Remote characteristic
static BLERemoteCharacteristic* pRemoteCharacteristic;

// Remote advertised device
static BLEAdvertisedDevice* myDevice;

static void notifyCallback(
  BLERemoteCharacteristic* pBLERemoteCharacteristic,
  uint8_t* pData,
  size_t length,
  bool isNotify) {
    pData[length] = '\0';
    String resp = String((char*)pData);

    String rVal = HandleResponse(resp);
    rVal.trim();
    String endTime = String(millis(), DEC);

    // Communicate back response
    SendMsgSerial(startTime + COMM_DELIM + rVal + COMM_DELIM + endTime);

    // Reset values
    lastRequest = "";
    startTime = "";
}

String HandleResponse(String resp) {
  int partSize = seperate(resp, sPtr, 3, COMM_DELIM);

  if (partSize < 3) {
    Serial.println("FAILED");
    return resp;
  }

  if (lastRequest.indexOf("DES") >= 0) {
    CopyToDESIn(sPtr[1]);
    _desLib.decrypt(_desOut, _desIn, _desKey);
    char out[9];
    std::memcpy(out, _desOut, 8);
    out[8] = '\0';
    String part = String(out, DEC);
    std::strcpy(sPtr[1], part.c_str());

  } else if (lastRequest.indexOf("AES") >= 0) {
    // Get the input
    String input = sPtr[1];

    char buffer[512];
    sprintf(buffer, "%s", input.c_str()); 
    uint16_t clen = input.length();
    
    String output = decryptToClearText(buffer, input.length(), aes_iv);

    for (int i = 0; i < 16; i++) {
      dec_iv[i] = 0;
    }
    std::strcpy(sPtr[1], output.c_str());
    
  }

  String rVal = "";
  for (int i = 0; i < 3; i++) {
    rVal += sPtr[i];
    rVal += COMM_DELIM;
  }

  return rVal;
}

class MyClientCallback : public BLEClientCallbacks {
  void onConnect(BLEClient* pclient) {
    connected = true;
  }

  void onDisconnect(BLEClient* pclient) {
    connected = false;
    Serial.println("onDisconnect");
  }
};

bool connectToServer() {
    Serial.print("Forming a connection to ");
    Serial.println(myDevice->getAddress().toString().c_str());
    
    BLEClient*  pClient  = BLEDevice::createClient();
    Serial.println(" - Created client");

    pClient->setClientCallbacks(new MyClientCallback());

    // Connect to the remove BLE Server.
    pClient->connect(myDevice);  // if you pass BLEAdvertisedDevice instead of address, it will be recognized type of peer device address (public or private)
    Serial.println(" - Connected to server");
    pClient->setMTU(517); //set client to request maximum MTU from server (default is 23 otherwise)
  
    // Obtain a reference to the service we are after in the remote BLE server.
    BLERemoteService* pRemoteService = pClient->getService(serviceUUID);
    if (pRemoteService == nullptr) {
      Serial.print("Failed to find our service UUID: ");
      Serial.println(serviceUUID.toString().c_str());
      pClient->disconnect();
      return false;
    }
    Serial.println(" - Found our service");


    // Obtain a reference to the characteristic in the service of the remote BLE server.
    pRemoteCharacteristic = pRemoteService->getCharacteristic(charUUID);
    if (pRemoteCharacteristic == nullptr) {
      Serial.print("Failed to find our characteristic UUID: ");
      Serial.println(charUUID.toString().c_str());
      pClient->disconnect();
      return false;
    }
    Serial.println(" - Found our characteristic");

    // Read the value of the characteristic.
    if(pRemoteCharacteristic->canRead()) {
      std::string value = pRemoteCharacteristic->readValue();
      Serial.print("The characteristic value was: ");
      Serial.println(value.c_str());
    }

    if(pRemoteCharacteristic->canNotify())
      pRemoteCharacteristic->registerForNotify(notifyCallback);
    else
      Serial.println("Cannot notify");

    connected = true;
    return true;
}

// Scanning results callback class
class MyAdvertisedDeviceCallbacks: public BLEAdvertisedDeviceCallbacks {

  // Result for advertized device callback
  void onResult(BLEAdvertisedDevice advertisedDevice) {
    // Check to see if found device
    //  contains the characteristic
    //  we are looking for
    if (advertisedDevice.haveServiceUUID() && advertisedDevice.isAdvertisingService(serviceUUID)) {
      BLEDevice::getScan()->stop();
      myDevice = new BLEAdvertisedDevice(advertisedDevice);
      doConnect = true;
      doScan = true;
    }
  }
};

// Setup
void setup() {
  // General initialization
  GenInit();

  Serial.println("General Init done");

  // Initalize BLE
  BLEDevice::init("");

  // Scanner setup
  BLEScan* pBLEScan = BLEDevice::getScan();
  pBLEScan->setAdvertisedDeviceCallbacks(new MyAdvertisedDeviceCallbacks());
  pBLEScan->setInterval(1349);
  pBLEScan->setWindow(449);
  pBLEScan->setActiveScan(true);
  pBLEScan->start(5, false);

  Serial.println("BLE active");
}

// Loop
void loop() {

  // Handle do connect
  if (doConnect == true) {
    if (connectToServer()) {
      Serial.println("We are now connected to the BLE Server.");
    } else {
      Serial.println("We have failed to connect to the server; there is nothin more we will do.");
    }
    doConnect = false;
  }

  // Handle connected
  if (connected) {
    // Read serial and make
    //  appropriate request
    String req = "";
    bool hasRequest = false;
    if (Serial.available() > 0) {
      req = Serial.readString();
      hasRequest = true;
    }

    if (!hasRequest) {
      delay(100);
      return;
    }

    // Save start time
    // The callback will use this
    //  to build the full serial
    //  response
    startTime = String(millis(), DEC);

    // Set request value into
    //  characteristic
    pRemoteCharacteristic->writeValue(req.c_str());
    lastRequest = req;
    
  }else if(doScan){
    BLEDevice::getScan()->start(5, false);
  }
  
  delay(1000); // Delay a second between loops.
} // End of loop

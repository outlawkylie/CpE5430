/*
    Based on Neil Kolban example for IDF: https://github.com/nkolban/esp32-snippets/blob/master/cpp_utils/tests/BLE%20Tests/SampleServer.cpp
    Ported to Arduino ESP32 by Evandro Copercini
    updates by chegewara
*/

#include <BLEDevice.h>
#include <BLEUtils.h>
#include <BLEServer.h>

#define SERVICE_UUID        "7089dd17-2180-41b5-bd34-646e0864625e"
#define CHARACTERISTIC_UUID "e2f7380a-887e-4849-9f3c-e2e06096a7c6"

BLEServer         *pServer;
BLEService        *pService;
BLECharacteristic *pCharacteristic;


void setup()
{
  Serial.begin(115200);

  BLEDevice::init("ESP32-BLE");
  pServer = BLEDevice::createServer();
  pService = pServer->createService(SERVICE_UUID);
  pCharacteristic = pService->createCharacteristic( CHARACTERISTIC_UUID,
                                                    BLECharacteristic::PROPERTY_READ |
                                                    BLECharacteristic::PROPERTY_WRITE
                                                    );

  pCharacteristic->setValue("CpE 5430 Project");
  pService->start();

  
  BLEAdvertising *pAdvertising = BLEDevice::getAdvertising();
  pAdvertising->addServiceUUID(SERVICE_UUID);
  pAdvertising->setScanResponse(true);
  pAdvertising->setMinPreferred(0x06);
  pAdvertising->setMinPreferred(0x12);
  BLEDevice::startAdvertising();
  
}

void loop()
{
  std::string value = pCharacteristic->getValue();
  delay(1000);
}

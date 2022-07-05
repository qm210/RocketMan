#pragma once

#include <Arduino.h>
#include <Vector.h>
#include <Preferences.h>

#include <BLEDevice.h>
#include <BLEServer.h>
#include <BLEUtils.h>
#include <BLE2902.h>

// UART UUIDs
#define SERVICE_UUID           "6E400001-B5A3-F393-E0A9-E50E24DCCA9E"
#define CHARACTERISTIC_UUID_RX "6E400002-B5A3-F393-E0A9-E50E24DCCA9E"
#define CHARACTERISTIC_UUID_TX "6E400003-B5A3-F393-E0A9-E50E24DCCA9E"

#define BLE_DEVICE_NAME "ROCKET-MAN"

enum RocketMessage {

};

class RocketManager
{
public:
    RocketManager();
    ~RocketManager() {};

    void setup();
    void handleInput();
    void store(boolean force = false);

    bool isConnected = false;
    bool wasConnected = false;
    Vector<std::string> received;

private:
    Preferences preferences;
    bool hasChanges;
    bool storeError;

    BLEServer *bleServer = NULL;
    BLECharacteristic *txChrct;
    BLECharacteristic *rxChrct;
};

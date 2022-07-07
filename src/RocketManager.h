#pragma once

#include <Arduino.h>
#include <Vector.h>
#include <String.h>
#include <Preferences.h>
#include "utils.h"
#include "patterns.h"
#include "PatternBase.h"

#include <BLEDevice.h>
#include <BLEServer.h>
#include <BLEUtils.h>
#include <BLE2902.h>

// UART UUIDs
#define SERVICE_UUID           "6E400001-B5A3-F393-E0A9-E50E24DCCA9E"
#define CHARACTERISTIC_UUID_RX "6E400002-B5A3-F393-E0A9-E50E24DCCA9E"
#define CHARACTERISTIC_UUID_TX "6E400003-B5A3-F393-E0A9-E50E24DCCA9E"

#define BLE_DEVICE_NAME "ROCKET-MAN"

class RocketManager
{
public:
    RocketManager();
    ~RocketManager() {};

    void setup();
    void handleInput();
    void store(boolean force = false);
    void setParameter(String target, int value);

    bool isConnected = false;
    bool wasConnected = false;
    Vector<String> received;

    int dritters_uv_dutycycle;
    RainbowOscillation *theRainbowOscillation;
    WhiteGlitter *theWhiteGlitter;

    PatternBase* allPatterns[2];

private:
    Preferences preferences;
    bool hasChanges;
    bool storeError;

    BLEServer *bleServer = NULL;
    BLECharacteristic *txChrct;
    BLECharacteristic *rxChrct;
};

#include "RocketManager.h"
#include "BleCallbacks.h"

RocketManager::RocketManager() {
    isConnected = false;
    wasConnected = false;
}

void RocketManager::setup() {
    BLEDevice::init(BLE_DEVICE_NAME);
    bleServer = BLEDevice::createServer();
    bleServer->setCallbacks(new ServerCallbacks(this));
    BLEService *bleService = bleServer->createService(SERVICE_UUID);
    txChrct = bleService->createCharacteristic(CHARACTERISTIC_UUID_TX, BLECharacteristic::PROPERTY_NOTIFY);
    txChrct->addDescriptor(new BLE2902());
    rxChrct = bleService->createCharacteristic(CHARACTERISTIC_UUID_RX, BLECharacteristic::PROPERTY_WRITE);
    rxChrct->setCallbacks(new ChrctCallbacks(this));
    bleService->start();

    // bleServer->getAdvertising()->addServiceUUID(bleService->getUUID());
    // bleServer->getAdvertising()->start();

    BLEAdvertising *advertising = BLEDevice::getAdvertising();
    advertising->addServiceUUID(SERVICE_UUID);
    advertising->setScanResponse(true);
    advertising->setMinPreferred(0x06);
    advertising->setMaxPreferred(0x12);
    BLEDevice::startAdvertising();

    String storage_array[32];
    received.setStorage(storage_array);
    delay(100);

    Serial.print("size of the messagedöner ");
    Serial.println(received.max_size());

    if (!preferences.begin("rocket-man", false)) {
        Serial.println("Access error on preferences.");
    }

    dritters_uv_dutycycle = preferences.getUInt("UV_B", 100);

    theRainbowOscillation = new RainbowOscillation();
    theRainbowOscillation->brightness = preferences.getUInt("RB_B", 150);
    theRainbowOscillation->fade_factor = preferences.getUInt("RB_FF", 250);
    theRainbowOscillation->frame_delay_ms = preferences.getUInt("RB_FD", 3);

    theWhiteGlitter = new WhiteGlitter();
    theWhiteGlitter->brightness = preferences.getUInt("GL_B", 220);
    theWhiteGlitter->spawn_threshold = preferences.getUInt("GL_C", 50);
    theWhiteGlitter->fade_factor = preferences.getUInt("GL_FF", 240);
    theWhiteGlitter->frame_delay_ms = preferences.getUInt("GL_FD", 5);

    allPatterns[0] = theRainbowOscillation;
    allPatterns[1] = theWhiteGlitter;
}

void RocketManager::handleInput() {
    while (!received.empty()) {
        auto received_part = String(received.front());
        received.remove(0);

        auto whitespace_pos = received_part.indexOf(' ');
        auto target = received_part.substring(0, whitespace_pos);
        auto value = received_part.substring(whitespace_pos + 1, received_part.length() - 1);
        Serial.print(target);
        Serial.print(";");
        Serial.println(value);

        setParameter(target, value.toInt());
    }
}

void RocketManager::setParameter(String target, int value) {
    // we expect value in [0, 255]
    hasChanges = true;
    if (target == "UV_B") {
        dritters_uv_dutycycle = value;
    }
    else if (target == "RB_B") {
        theRainbowOscillation->brightness = value;
    }
    else if (target = "RB_FF") {
        theRainbowOscillation->fade_factor = value;
    }
    else if (target == "GL_B") {
        theWhiteGlitter->brightness = value;
    }
    else if (target == "GL_FF") {
        theWhiteGlitter->fade_factor = value;
    }
    else if (target == "GL_FD") {
        theWhiteGlitter->frame_delay_ms = value;
    }
    else if (target == "GL_C") {
        theWhiteGlitter->spawn_threshold = value;
    }
}

void RocketManager::store(boolean force) {
    if (storeError)
        return;
    if (!hasChanges && !force)
        return;

    preferences.putUInt("UV_B", dritters_uv_dutycycle);
    preferences.putUInt("RB_B", theRainbowOscillation->brightness);
    preferences.putUInt("RB_FF", theRainbowOscillation->fade_factor);
    preferences.putUInt("RB_FD", theRainbowOscillation->frame_delay_ms);
    preferences.putUInt("GL_B", theWhiteGlitter->brightness);
    preferences.putUInt("GL_C", theWhiteGlitter->spawn_threshold);
    preferences.putUInt("GL_FF", theWhiteGlitter->fade_factor);
    preferences.putUInt("GL_FD", theWhiteGlitter->frame_delay_ms);
}

#include <Arduino.h>
#include <ArduinoBLE.h>
#include <Preferences.h>
#include "PatternBase.h"

enum RocketMessage {

}

class RocketManager
{
public:
    RocketManager() {};
    ~RocketManager() {};

    void setup();
    void handleInput();
    void store(boolean force);

private:
    Preferences preferences;
    boolean hasChanges;

    // Bluetooth® Low Energy LED Service
    static BLEService ledService("19B10000-E8F2-537E-4F6C-D104768A1214");
    // Bluetooth® Low Energy LED Switch Characteristic - custom 128-bit UUID, read and writable by central
    BLEByteCharacteristic switchCharacteristic("19B10001-E8F2-537E-4F6C-D104768A1214", BLERead | BLEWrite);

    static constexpr char* NAMESPACE = (char*)"rocket-man";
};

void RocketManager::setup() {
    if (!preferences.begin(NAMESPACE, false)) {
        Serial.println("Access error on preferences.");
    }
    if (!BLE.begin()) {
        Serial.println("BLE failed");
    })
    BLE.setLocalName("RocketMan");
    BLE.setAdvertisedService(ledService);
    ledService.addCharacteristic(switchCharacteristic);
    BLE.addService(ledService);
    switchCharacteristic.writeValue(0);
    BLE.advertise();

    // read
    // end
    Serial.println("Döner!");
}

void RocketManager::handleInput() {

}

void RocketManager::store(boolean force = false) {
    if (storeError)
        return;
    if (!hasChanges && !force)
        return;

    // preferences.begin
    // store
    // end
}

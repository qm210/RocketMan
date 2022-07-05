#include "RocketManager.h"

class ServerCallbacks: public BLEServerCallbacks {

    public:
        ServerCallbacks() = delete;
        ServerCallbacks(RocketManager* manager): manager(manager) {};

        void onConnect(BLEServer *bleServer) {
            manager->isConnected = true;
            Serial.println("is now connected!");
        }

        void onDisconnect(BLEServer *bleServer) {
            manager->isConnected = false;
            Serial.println("is now disconnected!");
        }

    private:
        RocketManager* manager;
};

class ChrctCallbacks: public BLECharacteristicCallbacks {

    public:
        ChrctCallbacks() = delete;
        ChrctCallbacks(RocketManager* manager): manager(manager) {};

        void onWrite(BLECharacteristic *pChrct) {
            std::string rxValue = pChrct->getValue();
            for(std::size_t i = 0; i < manager->received.size(); ++i) {
                if(manager->received[i][0] == rxValue[0]) {
                    Serial.print("OVERWRITE RECEIVED ");
                    Serial.println(manager->received[i][0]);
                    manager->received[i] = rxValue;
                    return;
                }
            }
            manager->received.push_back(rxValue);
        }

    private:
        RocketManager* manager;
};

RocketManager::RocketManager() {
    isConnected = false;
    wasConnected = false;
}

void RocketManager::setup() {
    if (!preferences.begin("rocket-man", false)) {
        Serial.println("Access error on preferences.");
    }
    // read
    // end

    BLEDevice::init(BLE_DEVICE_NAME);
    bleServer = BLEDevice::createServer();
    bleServer->setCallbacks(new ServerCallbacks(this));
    BLEService *bleService = bleServer->createService(SERVICE_UUID);
    txChrct = bleService->createCharacteristic(CHARACTERISTIC_UUID_TX, BLECharacteristic::PROPERTY_NOTIFY);
    txChrct->addDescriptor(new BLE2902());
    rxChrct = bleService->createCharacteristic(CHARACTERISTIC_UUID_RX, BLECharacteristic::PROPERTY_WRITE);
    rxChrct->setCallbacks(new ChrctCallbacks(this));
    bleService->start();
    bleServer->getAdvertising()->addServiceUUID(bleService->getUUID());
    bleServer->getAdvertising()->start();

    // BLEAdvertising *advertising = BLEDevice::getAdvertising();
    // advertising->addServiceUUID(SERVICE_UUID);
    // advertising->setScanResponse(true);
    // advertising->setMinPreferred(0x06);
    // advertising->setMaxPreferred(0x12);
    // BLEDevice::startAdvertising();

    Serial.println("Döner");
}

void RocketManager::handleInput() {

}

void RocketManager::store(boolean force) {
    if (storeError)
        return;
    if (!hasChanges && !force)
        return;

    // preferences.begin
    // store
    // end
}

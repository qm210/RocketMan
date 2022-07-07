#pragma once

#include "RocketManager.h"
#include <String.h>

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
            auto received_string = String(pChrct->getValue().c_str());
            manager->received.push_back(received_string);
        }

    private:
        RocketManager* manager;
};
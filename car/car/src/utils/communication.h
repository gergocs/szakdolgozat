//
// Created by csger on 2023-06-17.
//

#ifndef CAR_COMMUNICATION_H
#define CAR_COMMUNICATION_H

#include <WiFi.h>
#include <esp_now.h>

#include "state/State.h"
#include "config.h"

esp_now_peer_info_t peerInfo;

void onDataRecv(const uint8_t *mac, const uint8_t *data, int len) {
    memcpy(&State::getInstance().getInComingReadings(), data, sizeof(State::getInstance().getInComingReadings()));
    State::getInstance().setButtonValue(State::getInstance().getInComingReadings().buttonValue);
    State::getInstance().setReadXValue(State::getInstance().getInComingReadings().xValue);
    State::getInstance().setReadYValue(State::getInstance().getInComingReadings().yValue);
    State::getInstance().setIsDataValid(true);
}

void initESPNow() {
    WiFiClass::mode(WIFI_STA);

    if (esp_now_init() != ESP_OK) {
        Serial.println("Error initializing ESP-NOW");
        return;
    }

    memcpy(peerInfo.peer_addr, broadcastAddress, 6);
    peerInfo.channel = 0;
    peerInfo.encrypt = false;

    if (esp_now_add_peer(&peerInfo) != ESP_OK) {
        Serial.println("Failed to add peer");
        return;
    }

    esp_now_register_recv_cb(onDataRecv);

    Serial.println("ESPNow Init Success");
}

esp_err_t sendData() {
    if (State::getInstance().getIsDataReady()) {
        State::getInstance().setIsDataReady(false);

        return esp_now_send(broadcastAddress, (uint8_t *) &State::getInstance().getOutgoingReadings(),
                            sizeof(State::getInstance().getOutgoingReadings()));
    }

    return ESP_OK;
}

uint8_t readBattery() {
    return map(analogReadMilliVolts(batteryPin), 0, voltageMax, 0, 100);
}

#endif //CAR_COMMUNICATION_H

//
// Created by csger on 2023-07-30.
//

#ifndef CONTROLLER_COMMUNICATION_H
#define CONTROLLER_COMMUNICATION_H

#include <Arduino.h>
#include <WiFi.h>
#include <esp_now.h>

#include "graph/Graph.h"
#include "state/State.h"

esp_now_peer_info_t peerInfo;

void onDataRecv(const uint8_t *mac, const uint8_t *incomingData, int len) {
    memcpy(&State::getInstance().getInComingReadings(), incomingData,
           sizeof(State::getInstance().getInComingReadings()));
    if (State::getInstance().getInComingReadings().isBattery) {
        State::getInstance().getGraph()->printText(
                "Battery level: " + std::to_string(State::getInstance().getInComingReadings().readYValue) + "%");
        return;
    } else {
        State::getInstance().getGraph()->addData(State::getInstance().getInComingReadings().readYValue);
    }
}

bool initESPNow() {
    WiFi.mode(WIFI_STA);

    if (esp_now_init() != ESP_OK) {
        State::getInstance().getGraph()->printText("ESP-NOW INIT ERROR");
        return false;
    }

    memcpy(peerInfo.peer_addr, broadcastAddress, 6);
    peerInfo.channel = 0;
    peerInfo.encrypt = false;

    if (esp_now_add_peer(&peerInfo) != ESP_OK) {
        State::getInstance().getGraph()->printText("ESP-NOW PEER ERROR");
        return false;
    }

    esp_now_register_recv_cb(onDataRecv);

    return true;
}

#endif //CONTROLLER_COMMUNICATION_H

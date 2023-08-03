//
// Created by csger on 2023-07-30.
//

#ifndef CONTROLLER_COMMUNICATION_H
#define CONTROLLER_COMMUNICATION_H

#include <Arduino.h>
#include <WiFi.h>
#include <esp_now.h>

#include "graph/Graph.h"

constexpr uint8_t broadcastAddress[] = {0xC8, 0xF0, 0x9E, 0xF3, 0xD8, 0x08};

short readYValue = 0;

struct Outgoing {
    uint8_t xValue;
    uint8_t yValue;
};

extern Graph* graph;

Outgoing outgoingReadings;
esp_now_peer_info_t peerInfo;

void onDataRecv(const uint8_t *mac, const uint8_t *incomingData, int len) {
    memcpy(&readYValue, incomingData, sizeof(readYValue));
    //Serial.println(readYValue);
    graph->addData(readYValue);
}

void initESPNow() {
    WiFi.mode(WIFI_STA);

    if (esp_now_init() != ESP_OK) {
        graph->printText("ESP-NOW ERROR");
        return;
    }

    memcpy(peerInfo.peer_addr, broadcastAddress, 6);
    peerInfo.channel = 0;
    peerInfo.encrypt = false;

    if (esp_now_add_peer(&peerInfo) != ESP_OK) {
        graph->printText("ESP-NOW ERROR");
        return;
    }

    esp_now_register_recv_cb(onDataRecv);
}

#endif //CONTROLLER_COMMUNICATION_H

//
// Created by csger on 2023-06-17.
//

#ifndef CAR_COMMUNICATION_H
#define CAR_COMMUNICATION_H

#include <WiFi.h>
#include <esp_now.h>

struct InComing {
    uint8_t xValue;
    uint8_t yValue;
};

struct OutGoing {
    short speed;
};

InComing incomingData = {};
extern OutGoing outgoingData;

esp_now_peer_info_t peerInfo;

uint8_t broadcastAddress[] = {0x9C, 0x9C, 0x1F, 0xDC, 0x2C, 0xC0};

uint8_t readXValue = 0;
uint8_t readYValue = 0;

void onDataRecv(const uint8_t *mac, const uint8_t *data, int len) {
    memcpy(&incomingData, data, sizeof(incomingData));
    readXValue = incomingData.xValue;
    readYValue = incomingData.yValue;
}

void initESPNow(void) {
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
}

void sendData() {
    esp_now_send(broadcastAddress, (uint8_t *) &outgoingData, sizeof(outgoingData));
}

#endif //CAR_COMMUNICATION_H

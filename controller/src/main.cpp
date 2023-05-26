#include <Arduino.h>
#include <esp_now.h>
#include "WiFi.h"
#include "../lib/esp32-sh1106-oled-master/Adafruit_SH1106.h"
#include <Wire.h>
#include <queue>

#define SCREEN_WIDTH 128  // OLED display width, in pixels
#define SCREEN_HEIGHT 64  // OLED display height, in pixels
#define analogX 36        // X
#define analogY 39        // Y
#define SDA 21
#define SCL 22

int analogXValue = 0;
int analogYValue = 0;
short readYValue = 0;

std::deque<int> xQueue;

uint8_t broadcastAddress[] = {0xC8, 0xF0, 0x9E, 0xF3, 0xD8, 0x08};

struct Outgoing {
    int xValue;
    int yValue;
};

Outgoing outgoingReadings;
Adafruit_SH1106 display(SDA, SCL);

esp_now_peer_info_t peerInfo;

void onDataRecv(const uint8_t *mac, const uint8_t *incomingData, int len) {
    memcpy(&readYValue, incomingData, sizeof(readYValue));

    xQueue.push_back(readYValue);

    if (xQueue.size() > 110) {
        xQueue.pop_front();
    }
}

void setup() {
    // Init OLED display
    display.begin(SH1106_SWITCHCAPVCC, 0x3C);
    display.clearDisplay();

    WiFi.mode(WIFI_STA);

    if (esp_now_init() != ESP_OK) {
        display.println("ESP-NOW ERROR");
        return;
    }

    memcpy(peerInfo.peer_addr, broadcastAddress, 6);
    peerInfo.channel = 0;
    peerInfo.encrypt = false;

    if (esp_now_add_peer(&peerInfo) != ESP_OK) {
        display.println("ESP-NOW ERROR");
        return;
    }

    esp_now_register_recv_cb(onDataRecv);

    delay(3000);
}

void loop() {
    analogXValue = analogRead(analogX);
    analogYValue = analogRead(analogY);

    if (analogXValue < 100) {
        outgoingReadings.xValue = -2;
    } else if (analogXValue < 1000) {
        outgoingReadings.xValue = -1;
    } else if (analogXValue < 2000) {
        outgoingReadings.xValue = 0;
    } else if (analogXValue < 3500) {
        outgoingReadings.xValue = 1;
    } else {
        outgoingReadings.xValue = 2;
    }

    if (analogYValue < 100) {
        outgoingReadings.yValue = -2;
    } else if (analogYValue < 1000) {
        outgoingReadings.yValue = -1;
    } else if (analogYValue < 2000) {
        outgoingReadings.yValue = 0;
    } else if (analogYValue < 3500) {
        outgoingReadings.yValue = 1;
    } else {
        outgoingReadings.yValue = 2;
    }

    esp_err_t result = esp_now_send(broadcastAddress, (uint8_t *) &outgoingReadings, sizeof(outgoingReadings));

    if (result != ESP_OK) {
        display.println("Error");
    }

    display.clearDisplay();

    display.drawFastVLine(1, 1, SCREEN_HEIGHT - 2, WHITE);
    display.drawFastHLine(1, SCREEN_HEIGHT - 2, SCREEN_WIDTH - 1, WHITE);
    display.drawPixel(0, 2, WHITE);
    display.drawPixel(2, 2, WHITE);
    display.drawPixel(SCREEN_WIDTH - 2, SCREEN_HEIGHT - 1, WHITE);
    display.drawPixel(SCREEN_WIDTH - 2, SCREEN_HEIGHT - 3, WHITE);

    for (int i = 0; i < xQueue.size(); ++i) {
        display.drawPixel(i + 1, xQueue[i], WHITE);
    }

    display.display();
    delay(1);
}

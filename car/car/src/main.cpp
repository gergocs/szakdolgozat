#include <Arduino.h>
#include <WiFi.h>
#include <esp_now.h>

#include "carController/carController.h"

#define DEVICE_ADDRESS 0x05  // Maybe 0x01
#define M1_POWER 0x45
#define M2_POWER 0x46
#define NUMBER_OF_HOLES 20
#define interruptPin 39
#define RADIUS 0.02

int readXValue = 0;
int readYValue = 0;
uint32_t speedCounter = 0;
uint8_t broadcastAddress[] = {0x9C, 0x9C, 0x1F, 0xDC, 0x2C, 0xC0};

struct InComing {
    int xValue;
    int yValue;
};

struct OutGoing {
    int speed;
};

InComing incomingData = {};
OutGoing outgoingData = {};

CarController *carController = nullptr;

esp_now_peer_info_t peerInfo;

void onDataRecv(const uint8_t *mac, const uint8_t *data, int len) {
    memcpy(&incomingData, data, sizeof(incomingData));
    readXValue = incomingData.xValue;
    readYValue = incomingData.yValue;
}

void counter() {
    speedCounter++;
}

void move() {
    int moveX = 0;
    int moveY = 0;
    switch (readXValue) {
        case 0 ... 750: {
            moveX = 0;
            break;
        }
        case 751 ... 1500: {
            moveX = 1;
            break;
        }
        case 1501 ... 2500: {
            moveX = 2;
            break;
        }
        case 2501 ... 3500: {
            moveX = 3;
            break;
        }
        case 3501 ... 4095: {
            moveX = 4;
            break;
        }
        default: {
            moveX = 2;
        }
    }

    switch (readYValue) {
        case 0 ... 750: {
            moveY = 0;
            break;
        }
        case 751 ... 1500: {
            moveY = 1;
            break;
        }
        case 1501 ... 2500: {
            moveY = 2;
            break;
        }
        case 2501 ... 3500: {
            moveY = 3;
            break;
        }
        case 3501 ... 4095: {
            moveY = 4;
            break;
        }
        default: {
            moveY = 2;
        }
    }

    Serial.println(moveX);
    Serial.println(moveY);

    if (moveY < 2) {
        carController->left(moveY == 1 ? 50 : 100, 10); //TODO: Maybe change time
    } else if (moveY > 2) {
        carController->right(moveY == 3 ? 50 : 100, 10); //TODO: Maybe change time
    }

    if (moveX < 2) {
        carController->reverse(moveX == 1 ? 50 : 100, 10); //TODO: Maybe change time
    } else if (moveX > 2) {
        carController->straight(moveX == 3 ? 50 : 100, 10); //TODO: Maybe change time
    }

    if (moveX == 2 && moveY == 2) {
        carController->stop();
    }
}

void setup() {
    Serial.begin(9600);

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

    delay(5000);
    carController = new CarController(M1_POWER, M2_POWER, DEVICE_ADDRESS);
    delay(1000);

    pinMode(interruptPin, INPUT);
    attachInterrupt(digitalPinToInterrupt(interruptPin), counter, RISING);

    carController->straight(100, 10);
}

void loop() {
    /*if (readYValue == 0) {
        outgoingData.speed = (((speedCounter * 120) / NUMBER_OF_HOLES) * 2 * PI * RADIUS) / 60;
        if (readXValue < 0) {
            outgoingData.speed *= -1;
        }
    } else {
        outgoingData.speed = 0;
    }*/
    speedCounter = 0;

    //move();

    for (int i = 0; i < 20; ++i) {
        outgoingData.speed = i + (readXValue * 10) + 20;
        esp_now_send(broadcastAddress, (uint8_t *) &outgoingData, sizeof(outgoingData));
        delay(30);
    }

    for (int i = 20; i > 0; --i) {
        outgoingData.speed = i + (readXValue * 10) + 20;
        esp_now_send(broadcastAddress, (uint8_t *) &outgoingData, sizeof(outgoingData));
        delay(30);
    }

}

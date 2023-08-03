#include <Arduino.h>
#include "utils/communication.h"
#include "utils/interruptHandler.h"
#include "carController/carController.h"

CarController *carController = nullptr;

OutGoing outgoingData = {};

void move() {
    uint8_t moveX = readXValue;
    uint8_t moveY = readXValue;

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

    initESPNow();

    delay(5000);

    carController = new CarController(DaisyChainPosition::FIRST);
    carController->straight(100, 10);

    delay(1000);

    initInterrupts();
}

void loop() {
    //move();
}

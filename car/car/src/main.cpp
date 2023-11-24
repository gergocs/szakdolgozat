#include <Arduino.h>

#include "utils/communication.h"

void move() {
    uint8_t moveX = State::getInstance().getReadXValue();
    uint8_t moveY = State::getInstance().getReadYValue();
    bool button = State::getInstance().isButtonValue();

    if (auto time = millis(); time - State::getInstance().getRobotController()->getLastTime() > timeOfCheckMax) {
        auto speed = State::getInstance().getRobotController()->getCurrentSpeed(time,
                                                                                State::getInstance().getEncoder(0),
                                                                                State::getInstance().getEncoder(1));
        State::getInstance().getOutgoingReadings().speed = map(speed, minEncoderValue, maxEncoderValue, 0, 50);
        State::getInstance().getOutgoingReadings().isBattery = false;
        State::getInstance().setIsDataReady(true);
    }

    if (State::getInstance().getRobotController()->isCruseControl()) {
        if (button && moveX > moveMin && moveX < moveMax && moveY > moveMin && moveY < moveMax) {
            State::getInstance().getRobotController()->setCruseControl(false);
            State::getInstance().getRobotController()->setSpeed(0);
            State::getInstance().getRobotController()->setTargetSPeed(0);
            State::getInstance().getRobotController()->stop();
            delay(500);
            return;
        }

        State::getInstance().getRobotController()->start();
        delay(20);
        return;
    }

    if (button) {
        if (moveX < moveMin || moveX > moveMax) {
            State::getInstance().getRobotController()->setCruseControl(true);

            int16_t speed = std::abs(moveX - controllerCenter) * 2;

            State::getInstance().getRobotController()->setTargetSPeed(speed);

            if (moveX < moveMin) {
                State::getInstance().getRobotController()->reverse(speed);
            } else if (moveX > moveMax) {
                State::getInstance().getRobotController()->straight(speed);
            }
        } else {
            State::getInstance().getRobotController()->stop();
            delay(20);
            State::getInstance().getRobotController()->setCruseControl(false);
            State::getInstance().getOutgoingReadings().speed = readBattery();
            State::getInstance().getOutgoingReadings().isBattery = true;
            State::getInstance().setIsDataReady(true);
            return;
        }
    } else {
        int16_t speed = std::abs(moveX - controllerCenter) * 2;

        if (moveY < moveMin && speed > 20) { // TODO Check if this is correct
            State::getInstance().getRobotController()->left(speed);
        } else if (moveY > moveMax && speed > 20) {
            State::getInstance().getRobotController()->right(speed);
        } else {
            if (moveX < moveMin) {
                State::getInstance().getRobotController()->reverse(speed);
            } else if (moveX > moveMax) {
                State::getInstance().getRobotController()->straight(speed);
            } else {
                State::getInstance().getRobotController()->setSpeed(0);
                State::getInstance().getRobotController()->setTargetSPeed(0);
                State::getInstance().getRobotController()->stop();
                delay(20);
                return;
            }
        }
    }

    State::getInstance().getRobotController()->start();
    delay(20);
}

void setup() {
    Serial.begin(9600);

    while (!Serial);

    Serial.println();

    State::getInstance();
    initESPNow();

    while (!State::getInstance().isDataValid1()) {
        delay(100);
    }
}

void loop() {
    move();

    while (sendData() != ESP_OK) {
        State::getInstance().getRobotController()->stop();
        Serial.println("Error sending the data");
        delay(500);
        State::getInstance().setIsDataReady(true);
        delay(500);
    }
}

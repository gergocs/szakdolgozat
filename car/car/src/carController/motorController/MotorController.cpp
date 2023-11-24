//
// Created by csger on 2023-10-11.
//

#include "MotorController.h"
#include <Arduino.h>

MotorController::MotorController(const uint8_t controllerPin1, const uint8_t controllerPin2,
                                 const uint8_t enablePin) : controllerPin1(controllerPin1),
                                                            controllerPin2(controllerPin2),
                                                            enablePin(enablePin), power(0), direction(true) {
    pinMode(this->controllerPin1, OUTPUT);
    pinMode(this->controllerPin2, OUTPUT);
    pinMode(this->enablePin, OUTPUT);
    this->stop();
}

void MotorController::setPower(uint8_t newPower) {
    this->power = newPower;
}

void MotorController::setDirection(bool newDirection) {
    this->direction = newDirection;
}

void MotorController::start() {
    analogWrite(this->enablePin, this->power);
    digitalWrite(this->controllerPin1, this->direction);
    digitalWrite(this->controllerPin2, !this->direction);
}

void MotorController::stop() {
    analogWrite(this->enablePin, 0);
    digitalWrite(this->controllerPin1, HIGH);
    digitalWrite(this->controllerPin2, HIGH);
}

bool MotorController::isDirection() const {
    return direction;
}

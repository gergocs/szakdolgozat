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

void MotorController::setPower(uint8_t power) {
    this->power = power;
}

void MotorController::setDirection(bool direction) {
    this->direction = direction;
}

void MotorController::start() {
    analogWrite(this->enablePin, this->power);
    digitalWrite(this->controllerPin1, this->direction);
    digitalWrite(this->controllerPin2, !this->direction);

    //digitalWrite(enablePin, HIGH);
//
    //if (this->direction) {
    //    analogWrite(controllerPin1, this->power);
    //    analogWrite(controllerPin2, 0);
    //} else {
    //    analogWrite(controllerPin2, this->power);
    //    analogWrite(controllerPin1, 0);
    //}
}

void MotorController::stop() {
    analogWrite(this->enablePin, 0);
    digitalWrite(this->controllerPin1, HIGH);
    digitalWrite(this->controllerPin2, HIGH);

    //digitalWrite(enablePin, LOW);
    //analogWrite(controllerPin1, 255);
    //analogWrite(controllerPin2, 255);
}

bool MotorController::isDirection() const {
    return direction;
}

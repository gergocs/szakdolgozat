//
// Created by csger on 2023-10-13.
//

#include "PID.h"

#include <Arduino.h>

uint8_t PID::calculate(uint8_t input) {
    auto currentTime = millis();
    float deltaTime = (currentTime - this->prevT) / 1000.0f;
    auto error = input - this->target;

    this->errorHistory.push_back(error * deltaTime);

    if (this->errorHistory.size() > PID::window) {
        this->errorHistory.pop_front();
    }

    this->prevError = error;
    this->prevT = currentTime;

    return (PID::Kp * error) + (PID::Ki * this->calculateErrorHistory()) +
           (PID::Kd * ((error - this->prevError) / deltaTime));
}

void PID::setTarget(uint8_t target) {
    this->target = target;
}

int32_t PID::calculateErrorHistory() {
    int32_t sum = 0;

    for (auto &error: this->errorHistory) {
        sum += error;
    }

    return sum;
}

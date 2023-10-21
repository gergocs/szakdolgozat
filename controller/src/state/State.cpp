//
// Created by csger on 2023-09-26.
//

#include "State.h"

void IRAM_ATTR Timer0_ISR() {
    State::getInstance().getGraph()->clear();
    esp_deep_sleep_start();
}

State::State() : graph(std::make_unique<Graph>(displayAddress, sdaPin, sclPin)), errorCounter(0), timer(),
                 outgoingReadings({}), inComingReadings({}) {
    pinMode(buttonPin, INPUT_PULLUP);
    this->timer = timerBegin(0, 65535, true);
    timerAttachInterrupt(this->timer, &Timer0_ISR, true);
    timerAlarmWrite(this->timer, 375000, true);
    timerAlarmEnable(this->timer);
}

State::Outgoing &State::getOutgoingReadings() {
    return outgoingReadings;
}

State::InComing &State::getInComingReadings() {
    return inComingReadings;
}

const std::unique_ptr<Graph> &State::getGraph() const {
    return graph;
}

uint8_t State::getErrorCounter() const {
    return errorCounter;
}

void State::incrementErrorCounter() {
    this->errorCounter++;
}

void State::resetErrorCounter() {
    this->errorCounter = 0;
}

void State::resetTimer() {
    if (this->timer) {
        timerWrite(this->timer, 0);
    }
}

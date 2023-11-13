//
// Created by csger on 2023-09-26.
//

#include "State.h"

void IRAM_ATTR Timer0_ISR() {
    State::getInstance().setIsGoToSleep(true);
    /*esp_now_deinit();
    esp_deep_sleep_start();*/
}

State::State() : graph(std::make_unique<Graph>(displayAddress, sdaPin, sclPin)), errorCounter(0), timer(),
                 outgoingReadings({}), inComingReadings({}), isGoToSleep(false), isDataValid(false) {
    pinMode(buttonPin, INPUT_PULLUP);
    this->timer = timerBegin(0, divider, true);
    timerAttachInterrupt(this->timer, &Timer0_ISR, true);
    timerAlarmWrite(this->timer, waitTime, true);
    timerAlarmEnable(this->timer);

    Serial.println("State created");
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
    Serial.println("Resetting timer");
    if (this->timer) {
        timerWrite(this->timer, 0);
    }

    Serial.println("Alma");
}

bool State::isDataValid1() const {
    return isDataValid;
}

void State::setIsDataValid(bool isDataValid) {
    State::isDataValid = isDataValid;
}

bool State::isGoToSleep1() const {
    return isGoToSleep;
}

void State::setIsGoToSleep(bool isGoToSleep) {
    State::isGoToSleep = isGoToSleep;
}

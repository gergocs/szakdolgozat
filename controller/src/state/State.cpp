//
// Created by csger on 2023-09-26.
//

#include "State.h"

void IRAM_ATTR Timer0_ISR() {
    State::getInstance().setIsGoToSleep(true);
}

State::State() : graph(std::make_unique<Graph>(displayAddress, sdaPin, sclPin)), errorCounter(0), timer(),
                 outgoingReadings({}), inComingReadings({}), isGoToSleep(false), isDataValid(false) {
    pinMode(buttonPin, INPUT_PULLUP);
    this->timer = timerBegin(0, divider, true);
    timerAttachInterrupt(this->timer, &Timer0_ISR, true);
    timerAlarmWrite(this->timer, waitTime, true);
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

bool State::isDataValid1() const {
    return isDataValid;
}

void State::setIsDataValid(bool valid) {
    State::isDataValid = valid;
}

bool State::isGoToSleep1() const {
    return isGoToSleep;
}

void State::setIsGoToSleep(bool sleep) {
    State::isGoToSleep = sleep;
}

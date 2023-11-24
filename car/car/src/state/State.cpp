//
// Created by csger on 2023-09-26.
//

#include "State.h"

#include <esp_now.h>

void IRAM_ATTR Timer0_ISR() {
    esp_now_deinit();
    State::getInstance().getRobotController()->stop();
    esp_deep_sleep_start();
}

void IRAM_ATTR Encoder0_ISR() {
    State::getInstance().getEncoder(0).encoderCounter();
}

void IRAM_ATTR Encoder1_ISR() {
    State::getInstance().getEncoder(1).encoderCounter();
}

State::State() : encoders({Encoder(encoder0APin, encoder0BPin), Encoder(encoder1APin, encoder1BPin)}),
                 outgoingReadings({}), inComingReadings({}), readXValue(0), readYValue(0), buttonValue(false),
                 isDataReady(false), timer(),
                 robotController(std::make_unique<RobotController>()), isDataValid(false) {
    this->timer = timerBegin(0, divider, true);
    timerAttachInterrupt(this->timer, &Timer0_ISR, true);
    timerAlarmWrite(this->timer, waitTime, true);
    timerAlarmEnable(this->timer);

    attachInterrupt(digitalPinToInterrupt(encoder0APin), &Encoder0_ISR, CHANGE);
    attachInterrupt(digitalPinToInterrupt(encoder0BPin), &Encoder0_ISR, CHANGE);
    attachInterrupt(digitalPinToInterrupt(encoder1APin), &Encoder1_ISR, CHANGE);
    attachInterrupt(digitalPinToInterrupt(encoder1BPin), &Encoder1_ISR, CHANGE);

    this->robotController->stop();
    this->robotController->setTargetSPeed(0);
    this->inComingReadings.xValue = 127;
    this->inComingReadings.yValue = 127;
    this->inComingReadings.buttonValue = false;
}

State::OutGoing &State::getOutgoingReadings() {
    return outgoingReadings;
}

State::InComing &State::getInComingReadings() {
    return inComingReadings;
}

uint8_t State::getReadXValue() const {
    return readXValue;
}

uint8_t State::getReadYValue() const {
    return readYValue;
}

bool State::isButtonValue() const {
    return buttonValue;
}

void State::setReadXValue(uint8_t xValue) {
    State::readXValue = xValue;
}

void State::setReadYValue(uint8_t yValue) {
    State::readYValue = yValue;
}

void State::setButtonValue(bool bValue) {
    State::buttonValue = bValue;
}

const std::unique_ptr<RobotController> &State::getRobotController() const {
    return this->robotController;
}

volatile bool State::getIsDataReady() const {
    return isDataReady;
}

void State::setIsDataReady(volatile bool ready) {
    State::isDataReady = ready;
}

bool State::isDataValid1() const {
    return isDataValid;
}

void State::setIsDataValid(bool valid) {
    State::isDataValid = valid;
}

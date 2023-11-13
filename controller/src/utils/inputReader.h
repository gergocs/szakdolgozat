//
// Created by csger on 2023-07-30.
//

#ifndef CONTROLLER_INPUTREADER_H
#define CONTROLLER_INPUTREADER_H

#include <Arduino.h>

#include "communication.h"
#include "state/State.h"

void readInput() {
    auto analogXValue = analogRead(analogXPin);
    auto analogYValue = analogRead(analogYPin);
    auto buttonValue = digitalRead(buttonPin) == LOW;

    State::getInstance().getOutgoingReadings().xValue = map(analogXValue, 0, 4095, 0,
                                                            std::numeric_limits<uint8_t>::max());
    State::getInstance().getOutgoingReadings().yValue = map(analogYValue, 0, 4095, 0,
                                                            std::numeric_limits<uint8_t>::max());
    State::getInstance().getOutgoingReadings().buttonValue = buttonValue;

    if (!((State::getInstance().getOutgoingReadings().xValue < restartMax &&
           State::getInstance().getOutgoingReadings().xValue > restartMin) &&
          (State::getInstance().getOutgoingReadings().yValue < restartMax &&
           State::getInstance().getOutgoingReadings().yValue > restartMin))
        || State::getInstance().getOutgoingReadings().buttonValue) {
        Serial.println("Timer reset");
        State::getInstance().resetTimer();
    }
}

uint8_t readBattery() {
    return map(analogReadMilliVolts(batteryPin), 0, 3300, 0, 100);
}

#endif //CONTROLLER_INPUTREADER_H

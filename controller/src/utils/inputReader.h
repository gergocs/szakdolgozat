//
// Created by csger on 2023-07-30.
//

#ifndef CONTROLLER_INPUTREADER_H
#define CONTROLLER_INPUTREADER_H

#include <Arduino.h>
#include "Communication.h"
#include "interruptHandler.h"

void readInput(uint8_t xPin, uint8_t yPin, Outgoing& outgoing) {
    auto analogXValue = analogRead(xPin);
    auto analogYValue = analogRead(yPin);

    if (analogXValue < 100) {
        outgoing.xValue = 0;
    } else if (analogXValue < 1000) {
        outgoing.xValue = 1;
    } else if (analogXValue < 2000) {
        outgoing.xValue = 2;
    } else if (analogXValue < 3500) {
        outgoing.xValue = 3;
    } else {
        outgoing.xValue = 4;
    }

    if (analogYValue < 100) {
        outgoing.yValue = 0;
    } else if (analogYValue < 1000) {
        outgoing.yValue = 1;
    } else if (analogYValue < 2000) {
        outgoing.yValue = 2;
    } else if (analogYValue < 3500) {
        outgoing.yValue = 3;
    } else {
        outgoing.yValue = 4;
    }

    if (outgoing.xValue != 2 || outgoing.yValue != 2) {
        resetTimer();
    }
}

#endif //CONTROLLER_INPUTREADER_H

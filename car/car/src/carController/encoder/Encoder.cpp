//
// Created by csger on 2023-10-11.
//

#include "Encoder.h"
#include <Arduino.h>

Encoder::Encoder(uint8_t encoderPinA, uint8_t encoderPinB) : pos(0), lastEncoderPos(0),
                                                             encoderPinA(encoderPinA), encoderPinB(encoderPinB) {
    pinMode(this->encoderPinA, INPUT);
    pinMode(this->encoderPinB, INPUT);
    digitalWrite(this->encoderPinA, HIGH);
    digitalWrite(this->encoderPinB, HIGH);
}

void Encoder::encoderCounter() {
    auto current = (digitalRead(this->encoderPinA) << 1) | digitalRead(this->encoderPinB);
    auto sum = (this->lastEncoderPos << 2) | current;

    if (sum == 0b1101 || sum == 0b0100 || sum == 0b0010 || sum == 0b1011) {
        this->pos++;
    } else if (sum == 0b1110 || sum == 0b0111 || sum == 0b0001 || sum == 0b1000) {
        this->pos--;
    }

    this->lastEncoderPos = current;
}

int32_t Encoder::getPos() {
    return this->pos;
}

void Encoder::setPos(int32_t pos) {
    this->pos = pos;
}

int32_t Encoder::getPrevPos() const {
    return prevPos;
}

void Encoder::setPrevPos(int32_t prevPos) {
    Encoder::prevPos = prevPos;
}

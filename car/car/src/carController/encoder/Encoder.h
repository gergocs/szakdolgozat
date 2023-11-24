//
// Created by csger on 2023-10-11.
//

#ifndef CAR_ENCODER_H
#define CAR_ENCODER_H

#include <cstdint>

class Encoder {
public:
    Encoder(uint8_t encoderPinA, uint8_t encoderPinB);

    void encoderCounter();

    int32_t getPos();

    void setPos(int32_t pos);

    [[nodiscard]] int32_t getPrevPos() const;

    void setPrevPos(int32_t prevPos);

private:
    uint32_t lastEncoderPos;
    int32_t pos;
    int32_t prevPos;
    uint8_t encoderPinA;
    uint8_t encoderPinB;

};


#endif //CAR_ENCODER_H

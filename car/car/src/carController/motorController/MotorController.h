//
// Created by csger on 2023-10-11.
//

#ifndef CAR_MOTORCONTROLLER_H
#define CAR_MOTORCONTROLLER_H

#include <cstdint>

class MotorController {
public:
    MotorController(uint8_t controllerPin1, uint8_t controllerPin2, uint8_t enablePin);

    void setPower(uint8_t power);

    void setDirection(bool direction);

    void start();

    void stop();

    bool isDirection() const;

private:
    uint8_t controllerPin1;
    uint8_t controllerPin2;
    uint8_t enablePin;
    uint8_t power;
    bool direction; // true = forward, false = backward
};


#endif //CAR_MOTORCONTROLLER_H

#ifndef MOTOR_H
#define MOTOR_H

#include <Arduino.h>
#include <Wire.h>

class Motor {
public:
    Motor(uint8_t power, uint8_t address);

    void writeSpeed(int8_t speed) const;

private:
    uint8_t power;
    const uint8_t address;
};

#endif  //MOTOR_H
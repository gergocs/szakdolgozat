#ifndef CAR_CONTROLLER_H
#define CAR_CONTROLLER_H

#include <Arduino.h>
#include <Wire.h>

#include "carController/motor/motor.h"

#define TWI_FREQ 37390L  // reduce communication rate of I2C bus to 38.4 khz

// https://forum.arduino.cc/t/using-arduino-uno-to-control-hitechnic-motor-controller-over-i2c-bus/244161
class CarController {
public:
    CarController(uint8_t motor1Power, uint8_t motor2Power, uint8_t address);

    void stop();

    void left(int8_t power, long t);

    __attribute__((unused)) void right(int8_t power, long t);

    void straight(int8_t power, long t);

    __attribute__((unused)) void reverse(int8_t power, long t);

private:
    void motors(int8_t power1, int8_t power2);

    Motor motor1;
    Motor motor2;

    TwoWire wire = TwoWire(0);
};

#endif  //CAR_CONTROLLER_H
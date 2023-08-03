#ifndef CAR_CONTROLLER_H
#define CAR_CONTROLLER_H

#include "config.h"
#include <Arduino.h>
#include <Wire.h>

#if (ADVANCED_CONTROLLER == 0)

#include "carController/motor/motor.h"

#define M1_POWER 0x45
#define M2_POWER 0x46
#else
#include "carController/HiTechnicAdvancedControllers/HiTechnicDcMotorController.h"
#include "carController/HiTechnicAdvancedControllers/HiTechnicMotor.h"
#include <Wire.h>

using MotorPort = HiTechnicDcMotorController::MotorPort;
using RunMode = HiTechnicDcMotorController::RunMode;
using ZeroPowerBehavior = HiTechnicDcMotorController::ZeroPowerBehavior;
using Direction = HiTechnicMotor::Direction;
#endif

#include "carController/HiTechnicAdvancedControllers/HiTechnicController.h"
using DaisyChainPosition = HiTechnicController::DaisyChainPosition;

// https://forum.arduino.cc/t/using-arduino-uno-to-control-hitechnic-motor-controller-over-i2c-bus/244161
class CarController {
public:
#if (ADVANCED_CONTROLLER == 0)

    explicit CarController(DaisyChainPosition position);

#else
    explicit CarController(DaisyChainPosition position);
#endif

    void stop();

    void left(int8_t power, long t);

    void right(int8_t power, long t);

    void straight(int8_t power, long t);

    void reverse(int8_t power, long t);

private:
    void motors(int8_t power1, int8_t power2);

#if (ADVANCED_CONTROLLER == 0)
    Motor motor1;
    Motor motor2;
#else
    HiTechnicDcMotorController controller;
    HiTechnicMotor* leftDriveMotor;
    HiTechnicMotor* rightDriveMotor;
#endif
};

#endif  //CAR_CONTROLLER_H
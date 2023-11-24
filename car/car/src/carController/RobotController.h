#ifndef CAR_ROBOTCONTROLLER_H
#define CAR_ROBOTCONTROLLER_H

#include <Arduino.h>
#include <Wire.h>
#include <memory>

#include "config.h"
#include "carController/MotorController/MotorController.h"
#include "carController/PID/PID.h"
#include "carController/encoder/Encoder.h"

class RobotController {
public:
    RobotController();

    void stop();

    void start();

    void left(int16_t power);

    void right(int16_t power);

    void straight(int16_t power);

    void reverse(int16_t power);

    void setSpeed(int16_t speed);

    void setTargetSPeed(int16_t target);

    int16_t getCurrentSpeed(uint32_t time, Encoder &encoder1, Encoder &encoder2);

    [[nodiscard]] uint32_t getLastTime() const;

    [[nodiscard]] bool isCruseControl() const;

    void setCruseControl(bool enableCruseControl);

    virtual ~RobotController();

private:
    void setMotors(int16_t power1, int16_t power2);

    static int16_t capPower(int16_t power);

    bool cruseControl = false;

    uint32_t lastTime;

    std::array<MotorController, 2> motor;

    std::unique_ptr<Controller> controller;
};

#endif  //CAR_ROBOTCONTROLLER_H
#include "RobotController.h"

#include <Wire.h>

RobotController::RobotController() : motor({MotorController(controller0Pin1, controller0Pin2, controller0EnablePin),
                                            MotorController(controller1Pin1, controller1Pin2, controller1EnablePin)}),
                                     controller(std::make_unique<PID>()), lastTime(0) {
}

void RobotController::stop() {
    this->motor[0].stop();
    this->motor[1].stop();
}

void RobotController::start() {
    this->motor[0].start();
    this->motor[1].start();
}

void RobotController::left(int16_t power) {
    this->setMotors(power, power);
}

void RobotController::right(int16_t power) {
    this->left(-power);
}

void RobotController::straight(int16_t power) {
    this->setMotors(power, -power);
}

void RobotController::reverse(int16_t power) {
    this->straight(-power);
}

void RobotController::setMotors(int16_t power1, int16_t power2) {
    power1 = RobotController::capPower(power1);
    power2 = RobotController::capPower(power2);

    if (power1 < 0) {
        this->motor[0].setDirection(false);
    } else {
        this->motor[0].setDirection(true);
    }

    if (power2 < 0) {
        this->motor[1].setDirection(false);
    } else {
        this->motor[1].setDirection(true);
    }

    this->motor[0].setPower(std::abs(power1));
    this->motor[1].setPower(std::abs(power2));
}

int16_t RobotController::capPower(int16_t power) {
    if (power > motorPowerMax) {
        return motorPowerMax;
    } else if (power < motorPowerMin) {
        return motorPowerMin;
    }

    return power;
}

void RobotController::setSpeed(int16_t speed) {
    speed = this->controller->calculate(speed);

    if (this->motor[0].isDirection()) {
        this->setMotors(speed, -speed);
    } else {
        this->setMotors(-speed, speed);
    }
}

void RobotController::setTargetSpeed(int16_t target) {
    this->controller->setTarget(target);
}

int16_t RobotController::getCurrentSpeed(uint32_t time, Encoder &encoder1, Encoder &encoder2) {
    auto delta1 = encoder1.getPos() - encoder1.getPrevPos();
    auto delta2 = encoder2.getPos() - encoder2.getPrevPos();

    int speed = ((1000 * delta1) / (time - this->lastTime) +
                 (1000 * delta2) / (time - this->lastTime)) / 2;

    encoder1.setPrevPos(encoder1.getPos());
    encoder2.setPrevPos(encoder2.getPos());
    encoder1.setPos(0);
    encoder2.setPos(0);

    this->lastTime = time;

    if (this->cruseControl) {
        this->setSpeed(map(speed, minEncoderValue, maxEncoderValue, 0, motorPowerMax));
    }

    return speed;
}

uint32_t RobotController::getLastTime() const {
    return lastTime;
}

bool RobotController::isCruseControl() const {
    return cruseControl;
}

void RobotController::setCruseControl(bool enableCruseControl) {
    RobotController::cruseControl = enableCruseControl;
}

RobotController::~RobotController() = default;

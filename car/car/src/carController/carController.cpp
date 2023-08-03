#include "carController/carController.h"

#include <Wire.h>

#if (ADVANCED_CONTROLLER == 0)

CarController::CarController(DaisyChainPosition position)
        : motor1(M1_POWER, position), motor2(M2_POWER, position) {
    Serial.println("i2c speeeeed");
    Serial.println(Wire.begin(21, 22, TWI_FREQ));
    Serial.println(Wire.getClock());
}

#else

CarController::CarController(DaisyChainPosition position) : controller(position) {
    Wire.begin(21, 22, TWI_FREQ);
    Serial.println(Wire.getClock());

    char type[HiTechnicController::NUM_SENSOR_TYPE_CHARS];
    this->controller.getSensorType((uint8_t *) type);

    if (std::string str(type); str == "MotorCon") {
        Serial.print("--> Motor controller at daisy chain address ");
        Serial.println((int) DaisyChainPosition::FIRST);
    } else {
        Serial.print("ERROR: Expected MotorCon, got ");
        Serial.println(str.c_str());
    }

    this->leftDriveMotor = new HiTechnicMotor(&(this->controller), MotorPort::PORT_1);
    this->rightDriveMotor = new HiTechnicMotor(&(this->controller), MotorPort::PORT_2);
    this->leftDriveMotor->setPower(0);
    this->leftDriveMotor->setPower(0);
}

#endif

void CarController::stop() {
#if (ADVANCED_CONTROLLER == 0)
    this->motors(0, 0);
#else
    this->leftDriveMotor->setPower(0);
    this->rightDriveMotor->setPower(0);
#endif
}

void CarController::left(int8_t power, long t) {
    this->motors(power, power);
    delay(t);
    stop();
}

void CarController::right(int8_t power, long t) {
    this->left(-power, t);
}

void CarController::straight(int8_t power, long t) {
    this->motors(power, -power);
    delay(t);
    stop();
}

void CarController::reverse(int8_t power, long t) {
    this->straight(-power, t);
}

void CarController::motors(int8_t power1, int8_t power2) {
#if (ADVANCED_CONTROLLER == 0)
    this->motor1.writeSpeed(power1);
    this->motor2.writeSpeed(power2);
#else
    this->leftDriveMotor->setPower(power1);
    this->rightDriveMotor->setPower(power2);
#endif
}

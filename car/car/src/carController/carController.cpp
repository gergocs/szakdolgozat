#include "carController/carController.h"

#include <Wire.h>

CarController::CarController(uint8_t motor1Power, uint8_t motor2Power, uint8_t address)
        : motor1(motor1Power, address), motor2(motor2Power, address) {
    Serial.println("i2c speeeeed");
    Serial.println(this->wire.begin(21, 22, TWI_FREQ));
    Serial.println(this->wire.getClock());
}

void CarController::stop() {
    this->motor1.writeSpeed(0, &(this->wire));
    this->motor2.writeSpeed(0, &(this->wire));
}

void CarController::left(int8_t power, long t) {
    this->motor1.writeSpeed(power, &(this->wire));
    this->motor2.writeSpeed(power, &(this->wire));
    delay(t);
    stop();
}

__attribute__((unused)) void CarController::right(int8_t power, long t) {
    this->left(-power, t);
}

void CarController::straight(int8_t power, long t) {
    this->motors(power, -power);
    delay(t);
    stop();
}

__attribute__((unused)) void CarController::reverse(int8_t power, long t) {
    this->straight(-power, t);
}

void CarController::motors(int8_t power1, int8_t power2) {
    this->motor1.writeSpeed(power1, &(this->wire));
    this->motor2.writeSpeed(power2, &(this->wire));
}

#include "carController.h"

#include <Wire.h>

CarController::CarController(uint8_t motor1Power, uint8_t motor2Power, uint8_t address)
  : motor1(motor1Power, address), motor2(motor2Power, address) {
  Wire.setClock(TWI_FREQ);
  Wire.begin();
}

void CarController::stop(void) {
  this->motor1.writeSpeed(0);
  this->motor2.writeSpeed(0);
}

void CarController::left(uint8_t power, long t) {
  this->motor1.writeSpeed(power);
  this->motor2.writeSpeed(power);
  delay(t);
  stop();
}

void CarController::right(uint8_t power, long t) {
  this->left(-power, t);
}

void CarController::straight(uint8_t power, long t) {
  this->motors(power, -power);
  delay(t);
  stop();
}

void CarController::reverse(uint8_t power, long t) {
  this->straight(-power, t);
}

void CarController::motors(uint8_t power1, uint8_t power2) {
  this->motor1.writeSpeed(power1);
  this->motor2.writeSpeed(power2);
}

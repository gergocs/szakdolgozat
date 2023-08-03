#include "carController/motor/motor.h"

#include <Wire.h>

Motor::Motor(uint8_t power, uint8_t address)
        : power(power), address(address) {
}

void Motor::writeSpeed(int8_t speed) const {
    // if speed is between -100 and 100
    if (-100 <= speed && speed <= 100) {
        // set motor 1 to percentage value
        Wire.beginTransmission(this->address);  //begin transmission at DEVICE_ADDRESS (connect to device 0x05
        Wire.write(this->power);                // write to motor 1 power address
        Wire.write(speed);                   // send the data byte;
        Wire.endTransmission();                 // send a restart message to keep the connection alive (false(0));
    }
}
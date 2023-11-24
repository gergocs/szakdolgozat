//
// Created by csger on 2023-06-17.
//

#ifndef CAR_CONFIG_H
#define CAR_CONFIG_H

#include <cstdint>
#include <limits>

//constexpr uint8_t broadcastAddress[] = {0x9C, 0x9C, 0x1F, 0xDC, 0x2C, 0xC0};
constexpr uint8_t broadcastAddress[] = {0xB0, 0xA7, 0x32, 0x2B, 0xD7, 0xAC};

constexpr uint8_t encoder0APin = 22;
constexpr uint8_t encoder0BPin = 23;
constexpr uint8_t encoder1APin = 36;
constexpr uint8_t encoder1BPin = 39;
constexpr uint8_t batteryPin = 34;

constexpr uint8_t controller0Pin1 = 12;
constexpr uint8_t controller0Pin2 = 14;
constexpr uint8_t controller0EnablePin = 27;
constexpr uint8_t controller1Pin1 = 26;
constexpr uint8_t controller1Pin2 = 25;
constexpr uint8_t controller1EnablePin = 33;

constexpr uint8_t restartOffset = 15;
constexpr uint8_t controllerCenter = std::numeric_limits<uint8_t>::max() / 2;
constexpr uint8_t moveMin = controllerCenter - restartOffset;
constexpr uint8_t moveMax = controllerCenter + restartOffset;
constexpr uint8_t timeOfCheckMax = 30;
constexpr uint32_t waitTime = 300000000;
constexpr uint8_t divider = 80;

constexpr int16_t motorPowerMin = -255;
constexpr int16_t motorPowerMax = 255;

constexpr uint16_t voltageMax = 3000; // Max Voltage of batteries in mV

constexpr int8_t minEncoderValue = -70;
constexpr int8_t maxEncoderValue = 70;

#endif //CAR_CONFIG_H

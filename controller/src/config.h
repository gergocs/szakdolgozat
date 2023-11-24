//
// Created by csger on 2023-09-26.
//

#ifndef CONTROLLER_CONFIG_H
#define CONTROLLER_CONFIG_H

#include <cstdint>

constexpr uint8_t sdaPin = 21;
constexpr uint8_t sclPin = 22;
constexpr uint8_t buttonPin = 23;
constexpr uint8_t analogXPin = 36;
constexpr uint8_t analogYPin = 39;
constexpr uint8_t batteryPin = 34;

constexpr uint8_t displayAddress = 0x3C;
constexpr int16_t displayGraphWidth = 120;
constexpr int16_t displayGraphHeight = 60;

constexpr uint8_t broadcastAddress[] = {0xB0, 0xA7, 0x32, 0x2B, 0x51, 0x0C};

constexpr uint8_t espNowErrorMax = 100;
constexpr uint8_t restartOffset = 20;
constexpr uint8_t controllerCenter = std::numeric_limits<uint8_t>::max() / 2;
constexpr uint8_t restartMin = controllerCenter - restartOffset;
constexpr uint8_t restartMax = controllerCenter + restartOffset;
constexpr uint32_t waitTime = 300000000;
constexpr uint8_t divider = 80;

constexpr uint16_t adcMax = 4095;
constexpr uint16_t voltageMax = 2300; // Max Voltage of batteries in mV

#endif //CONTROLLER_CONFIG_H

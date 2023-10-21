//
// Created by csger on 2023-10-13.
//

#ifndef CAR_PID_H
#define CAR_PID_H

#include <cstdint>
#include <deque>

#include "carController/controller/Controller.h"

class PID : public Controller {

public:
    uint8_t calculate(uint8_t input) override;

    void setTarget(uint8_t target) override;

private:
    int32_t calculateErrorHistory();

    constexpr static float Kp = 2.5;
    constexpr static float Ki = 0.1;
    constexpr static float Kd = 0.2;
    constexpr static uint8_t window = 10;

    int16_t prevError = 0;
    uint32_t prevT = 0;

    std::deque<int16_t> errorHistory;
};


#endif //CAR_PID_H

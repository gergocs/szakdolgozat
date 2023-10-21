//
// Created by csger on 2023-09-26.
//

#ifndef CAR_STATE_H
#define CAR_STATE_H


#include <cstdint>
#include <esp32-hal-timer.h>
#include <memory>

#include "carController/RobotController.h"
#include "carController/Encoder/Encoder.h"
#include "carController/PID/PID.h"

class State {
public:
    struct InComing {
        uint8_t xValue;
        uint8_t yValue;
        bool buttonValue;
    };

    struct OutGoing {
        uint8_t speed;
        bool isBattery;
    };

    static State &getInstance() {
        static State instance;
        return instance;
    }

    [[nodiscard]] OutGoing &getOutgoingReadings();

    [[nodiscard]] InComing &getInComingReadings();

    [[nodiscard]] uint8_t getReadXValue() const;

    [[nodiscard]] uint8_t getReadYValue() const;

    [[nodiscard]] bool isButtonValue() const;

    void setReadXValue(uint8_t readXValue);

    void setReadYValue(uint8_t readYValue);

    void setButtonValue(bool buttonValue);

    [[nodiscard]] const std::unique_ptr<RobotController> &getRobotController() const;

    [[nodiscard]] volatile bool getIsDataReady() const;

    void setIsDataReady(volatile bool isDataReady);

    Encoder &getEncoder(uint8_t index) {
        return encoders[index];
    }

    bool isDataValid1() const;

    void setIsDataValid(bool isDataValid);

private:
    State();

    OutGoing outgoingReadings{};
    InComing inComingReadings{};

    bool isDataValid;
    bool isDataReady;
    bool buttonValue;
    uint8_t readXValue;
    uint8_t readYValue;
    hw_timer_t *timer;
    std::unique_ptr<RobotController> robotController;
    std::array<Encoder, 2> encoders;
};


#endif //CAR_STATE_H

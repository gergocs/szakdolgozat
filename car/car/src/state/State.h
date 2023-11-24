//
// Created by csger on 2023-09-26.
//

#ifndef CAR_STATE_H
#define CAR_STATE_H


#include <cstdint>
#include <esp32-hal-timer.h>
#include <memory>

#include "carController/RobotController.h"
#include "carController/encoder/Encoder.h"
#include "carController/PID/PID.h"

class State {
public:
    struct InComing {
        uint8_t xValue;
        uint8_t yValue;
        bool buttonValue;
    };

    struct OutGoing {
        [[maybe_unused]] uint8_t speed;
        [[maybe_unused]] bool isBattery;
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

    void setReadXValue(uint8_t xValue);

    void setReadYValue(uint8_t yValue);

    void setButtonValue(bool bValue);

    [[nodiscard]] const std::unique_ptr<RobotController> &getRobotController() const;

    [[nodiscard]] volatile bool getIsDataReady() const;

    void setIsDataReady(volatile bool ready);

    Encoder &getEncoder(uint8_t index) {
        return encoders[index];
    }

    [[nodiscard]] bool isDataValid1() const;

    void setIsDataValid(bool valid);

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

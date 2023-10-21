//
// Created by csger on 2023-09-26.
//

#ifndef CONTROLLER_STATE_H
#define CONTROLLER_STATE_H


#include <cstdint>
#include <memory>
#include <esp_now.h>

#include "graph/Graph.h"
#include "config.h"

class State {
public:
    static State &getInstance() {
        static State instance;
        return instance;
    }

    struct InComing {
        uint8_t readYValue;
        bool isBattery;
    };

    struct Outgoing {
        uint8_t xValue;
        uint8_t yValue;
        bool buttonValue;
    };

    [[nodiscard]] Outgoing &getOutgoingReadings();

    [[nodiscard]] InComing &getInComingReadings();

    [[nodiscard]] const std::unique_ptr<Graph> &getGraph() const;

    uint8_t getErrorCounter() const;

    void incrementErrorCounter();

    void resetErrorCounter();

    void resetTimer();

private:
    State();

    Outgoing outgoingReadings;
    InComing inComingReadings;
    std::unique_ptr<Graph> graph;
    uint8_t errorCounter;
    hw_timer_t *timer;
};


#endif //CONTROLLER_STATE_H

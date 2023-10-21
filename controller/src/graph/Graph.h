//
// Created by csger on 2023-07-30.
//

#ifndef CONTROLLER_GRAPH_H
#define CONTROLLER_GRAPH_H

#include <memory>
#include <deque>

#include "Adafruit_SH1106.h"

class Graph {
public:
    Graph(uint8_t address, int8_t sda, int8_t scl);

    void drawAxis(int16_t x0, int16_t y0, int16_t x1, int16_t y1);

    void drawData();

    void printText(std::string_view text);

    void addData(int16_t data);

    void clear();

private:
    int16_t xStart = 0;
    int16_t yStart = 0;
    int16_t xEnd = 0;
    int16_t yEnd = 0;
    std::unique_ptr<Adafruit_SH1106> display;
    std::deque<int16_t> points;
};


#endif //CONTROLLER_GRAPH_H

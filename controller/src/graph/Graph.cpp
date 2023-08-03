//
// Created by csger on 2023-07-30.
//

#include "Graph.h"

#include <memory>

Graph::Graph(uint8_t address, int8_t sda, int8_t scl) {
    display = std::make_unique<Adafruit_SH1106>(sda, scl);
    display->begin(SH1106_SWITCHCAPVCC, address);
    display->display();
    display->clearDisplay();
    display->setTextSize(1);
    display->setTextColor(WHITE);
    this->xStart = 0;
    this->yStart = 0;
    this->xEnd = 120;
    this->yEnd = 60;
    this->points = std::deque<int16_t>();
}

void Graph::drawAxis(int16_t x0, int16_t y0, int16_t x1, int16_t y1) {
    this->xStart = x0;
    this->yStart = y0;
    this->xEnd = x1;
    this->yEnd = y1;

    display->drawLine(this->xStart, this->yEnd, this->xEnd, this->yEnd, WHITE);
    display->drawLine(this->xStart, this->yStart, this->xStart, this->yEnd, WHITE);

    for (int32_t i = 0; i < (((this->yEnd - this->yStart) * 100) / 500); i++)
    {
        display->drawLine(this->xStart - 1, this->yEnd - (i + 1) * 5, this->xStart + 1, this->yEnd - (i + 1) * 5, WHITE);
    }

    for (int32_t i = 0; i < (((this->xEnd - this->xStart) * 100) / 500); i++)
    {
        display->drawLine(this->xStart + (i + 1) * 5, this->yEnd - 1, this->xStart + (i + 1) * 5, this->yEnd + 1, WHITE);
    }
}

void Graph::addData(int16_t data) {

    if (this->points.size() > 120) {
        this->points.pop_front();
    }

    this->points.push_back(data);
}

void Graph::drawData() {
    display->clearDisplay();
    this->drawAxis(this->xStart, this->yStart, this->xEnd, this->yEnd);

    if (this->points.size() >= 2) {
        for (int i = 1; i < this->points.size(); ++i) {
            display->drawLine(i -1, this->points[i - 1], i, this->points[i], WHITE);
        }
    }

    display->display();
}

void Graph::printText(std::string_view text) {
    display->clearDisplay();
    display->setCursor(0, 0);
    display->println(text.data());
    display->display();
}

void Graph::clear(void) {
    display->clearDisplay();
    display->display();
}

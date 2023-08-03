//
// Created by csger on 2023-08-02.
//

#ifndef CONTROLLER_INTERRUPTHANDLER_H
#define CONTROLLER_INTERRUPTHANDLER_H

#include <Arduino.h>

extern Graph* graph;

hw_timer_t *timer = nullptr;

void IRAM_ATTR Timer0_ISR()
{
    graph->clear();
    esp_deep_sleep_start();
}

void initInterrupt() {
    timer = timerBegin(0, 65535, true);
    timerAttachInterrupt(timer, &Timer0_ISR, true);
    timerAlarmWrite(timer, 375000, true);
    timerAlarmEnable(timer);
}

void resetTimer() {
    if (timer) {
        timerWrite(timer, 0);
    }
}

#endif //CONTROLLER_INTERRUPTHANDLER_H

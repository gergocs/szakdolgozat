//
// Created by csger on 2023-08-03.
//

#ifndef CAR_INTERRUPTHANDLER_H
#define CAR_INTERRUPTHANDLER_H

#define interruptPin 39
#define NUMBER_OF_HOLES 20
#define RADIUS 0.02

constexpr uint8_t center = 27;

hw_timer_t *Timer0_Cfg = nullptr;

uint32_t speedCounter = 0;

void counter() {
    speedCounter++;
}

void IRAM_ATTR Timer0_ISR()
{
    outgoingData.speed = speedCounter * 120 / NUMBER_OF_HOLES;

    if (readXValue > 2) {
        outgoingData.speed *= -1;
    }

    outgoingData.speed = center - outgoingData.speed;

    if (outgoingData.speed > 60) {
        outgoingData.speed = 60;
    } else if (outgoingData.speed < 0) {
        outgoingData.speed = 2;
    }

    sendData();

    speedCounter = 0;
}

void initInterrupts() {
    pinMode(interruptPin, INPUT);
    attachInterrupt(digitalPinToInterrupt(interruptPin), counter, RISING);
    Timer0_Cfg = timerBegin(0, 80, true);
    timerAttachInterrupt(Timer0_Cfg, &Timer0_ISR, true);
    timerAlarmWrite(Timer0_Cfg, 1000000, true);
    timerAlarmEnable(Timer0_Cfg);
}

#endif //CAR_INTERRUPTHANDLER_H

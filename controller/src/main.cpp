#include <Arduino.h>

#include "utils/communication.h"

void setup() {
    State::getInstance().getGraph()->printText("Preparing the communication...");

    delay(1000);

    if (initESPNow()) {
        State::getInstance().getGraph()->printText("Communication ready!");
    } else {
        State::getInstance().getGraph()->printText("Error initializing the communication");
        delay(10000);
        ESP.restart();
    }

    delay(3000);

    State::getInstance().getOutgoingReadings().buttonValue = true;
    State::getInstance().getOutgoingReadings().xValue = controllerCenter;
    State::getInstance().getOutgoingReadings().yValue = controllerCenter;


    while (!State::getInstance().isDataValid1()) {
        esp_now_send(broadcastAddress, (uint8_t *) &State::getInstance().getOutgoingReadings(),
                     sizeof(State::getInstance().getOutgoingReadings()));
        delay(100);

        State::getInstance().getGraph()->printText(
                "Waiting for robot\nCont. battery: " + std::to_string(readBattery()) + "%");

        if (State::getInstance().isGoToSleep1()) {
            State::getInstance().getGraph()->clear();
            esp_now_deinit();
            esp_deep_sleep_start();
        }
    }

    State::getInstance().getGraph()->printText("Connected!");

    delay(1000);

    if (!State::getInstance().getInComingReadings().isBattery) {
        State::getInstance().getGraph()->drawData();
    } else {
        delay(5000);
    }
}

void loop() {
    if (State::getInstance().isGoToSleep1()) {
        esp_now_deinit();
        State::getInstance().getGraph()->clear();
        esp_deep_sleep_start();
    }

    readInput();

    esp_err_t result = esp_now_send(broadcastAddress,
                                    (uint8_t *) &State::getInstance().getOutgoingReadings(),
                                    sizeof(State::getInstance().getOutgoingReadings()));

    if (result != ESP_OK) {
        State::getInstance().incrementErrorCounter();

        if (State::getInstance().getErrorCounter() > espNowErrorMax) {
            State::getInstance().getGraph()->printText(
                    "Error sending data please check connection and restart the device");

            delay(10000);

            ESP.restart();
        }
    } else {
        State::getInstance().resetErrorCounter();
    }

    if (!State::getInstance().getInComingReadings().isBattery) {
        State::getInstance().getGraph()->drawData();
    }

    delay(10);
}

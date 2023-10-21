#include <Arduino.h>

#include "utils/inputReader.h"
#include "utils/communication.h"

void setup() {
    Serial.begin(9600);

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

    State::getInstance().getGraph()->printText("Ready");

    delay(1000);
}

void loop() {
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

#include <Arduino.h>
#include "utils/inputReader.h"
#include "utils/interruptHandler.h"
#include "graph/Graph.h"

constexpr int8_t sdaPin = 21;
constexpr int8_t sclPin = 22;
constexpr int8_t analogXPin = 36;
constexpr int8_t analogYPin = 39;
constexpr uint8_t displayAddress = 0x3C;

Graph* graph = nullptr;

#include "utils/Communication.h"

void setup() {
    Serial.begin(9600);
    graph = new Graph(displayAddress, sdaPin, sclPin);

    initESPNow();

    delay(3000);

    initInterrupt();
}

void loop() {
    readInput(analogXPin, analogYPin, outgoingReadings);

    esp_err_t result = esp_now_send(broadcastAddress, (uint8_t *) &outgoingReadings, sizeof(outgoingReadings));

    if (result != ESP_OK) {
        graph->printText("Error");
    } else {
        graph->drawData();
    }

    delay(1);
}

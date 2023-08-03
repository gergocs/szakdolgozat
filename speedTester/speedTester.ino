#include <esp_timer.h>

#define number_of_holes 20
#define interruptPin 39

uint32_t i = 0;

void setup() {
  pinMode(interruptPin, INPUT);
  attachInterrupt(digitalPinToInterrupt(interruptPin), counter, RISING);
  Serial.begin(9600);
}

void loop() {
  delay(500);
  Serial.print("Speed:  ");
  Serial.print(i * 120 / number_of_holes);
  Serial.println(" rpm");
  i = 0;
}

void counter() {
  i++;
}

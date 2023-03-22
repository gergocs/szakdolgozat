#include <esp_now.h>
#include "WiFi.h"
 
int readXValue = 0;
int readYValue = 0;
uint8_t broadcastAddress[] = {0x9C, 0x9C, 0x1F, 0xDC, 0x2C, 0xC0}; // TODO: Replace with the mac address

typedef struct struct_message {
  int xValue;
  int yValue;
} struct_message;

struct_message incomingReadings;
struct_message outgoingReadings;

esp_now_peer_info_t peerInfo;

void onDataRecv(const uint8_t* mac, const uint8_t* incomingData, int len) {
  memcpy(&incomingReadings, incomingData, sizeof(incomingReadings));
  readXValue = incomingReadings.xValue;
  readYValue = incomingReadings.yValue;
}

void setup(){
  Serial.begin(9600);
  WiFi.mode(WIFI_STA);

  if (esp_now_init() != ESP_OK) {
    Serial.println("Error initializing ESP-NOW");
    return;
  }

  memcpy(peerInfo.peer_addr, broadcastAddress, 6);
  peerInfo.channel = 0;  
  peerInfo.encrypt = false;

  if (esp_now_add_peer(&peerInfo) != ESP_OK){
    Serial.println("Failed to add peer");
    return;
  }

  esp_now_register_recv_cb(onDataRecv);
}

void loop(){
  outgoingReadings.xValue = readXValue;
  outgoingReadings.yValue = readYValue;
  Serial.println(readYValue);
  esp_err_t result = esp_now_send(broadcastAddress, (uint8_t*) &outgoingReadings, sizeof(outgoingReadings));

  delay(100);
}
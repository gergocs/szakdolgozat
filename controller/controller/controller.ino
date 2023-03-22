#include <esp_now.h>
#include "WiFi.h"
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SH1106.h>

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels
#define analogX 36 // X
#define analogY 39 // Y
#define SDA 21
#define SCL 22

int analogXValue = 0;
int analogYValue = 0;
int readXValue = 0;
int readYValue = 0;

uint8_t broadcastAddress[] = {0xC8, 0xF0, 0x9E, 0xF3, 0xD8, 0x08};

typedef struct struct_message {
  int xValue;
  int yValue;
} struct_message;

struct_message incomingReadings;
struct_message outgoingReadings;

Adafruit_SH1106 display(SDA, SCL);

esp_now_peer_info_t peerInfo;

void onDataRecv(const uint8_t* mac, const uint8_t* incomingData, int len) {
  memcpy(&incomingReadings, incomingData, sizeof(incomingReadings));
  readXValue = incomingReadings.xValue;
  readYValue = incomingReadings.yValue;
}

void setup(){
  // Init OLED display
  display.begin(SH1106_SWITCHCAPVCC, 0x3C); 
  display.clearDisplay();

  WiFi.mode(WIFI_STA);

  if (esp_now_init() != ESP_OK) {
    display.println("ESP-NOW");
    return;
  }

  memcpy(peerInfo.peer_addr, broadcastAddress, 6);
  peerInfo.channel = 0;  
  peerInfo.encrypt = false;

  if (esp_now_add_peer(&peerInfo) != ESP_OK){
    display.println("ESP-NOW");
    return;
  }

  esp_now_register_recv_cb(onDataRecv);
}
 
void loop(){
  display.setTextSize(2);
  display.setTextColor(WHITE);
  display.setCursor(0,0);

  outgoingReadings.xValue = analogXValue;
  outgoingReadings.yValue = analogYValue;

  esp_err_t result = esp_now_send(broadcastAddress, (uint8_t*) &outgoingReadings, sizeof(outgoingReadings));

  if (result != ESP_OK) {
    display.println("Error");
  } else {
    display.println("x="+String(readXValue));
    display.println("y="+String(readYValue));
  }

  display.display();
  delay(10);
  display.clearDisplay();

  analogXValue = analogRead(analogX);
  analogYValue = analogRead(analogY);

  delay(100);
}
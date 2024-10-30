#include <ESP8266WiFi.h>
#include <espnow.h>

uint8_t broadcastAddress[] = {0xE0, 0x98, 0x06, 0x99, 0xA2, 0x1C};
#define BOARD_ID 2

typedef struct struct_message {
    int id;
    int x;
    int y;
    int z;
    int w;
} struct_message;

struct_message myData;

void OnDataSent(uint8_t *mac_addr, uint8_t sendStatus) {
  Serial.print("\r\nLast Packet Send Status: ");
  Serial.println(sendStatus == 0 ? "Delivery success" : "Delivery fail");
}
 
void setup() {
  Serial.begin(9600);
  WiFi.mode(WIFI_STA);
  WiFi.disconnect();

  if (esp_now_init() != 0) {
    Serial.println("Error initializing ESP-NOW");
    return;
  } 

  esp_now_set_self_role(ESP_NOW_ROLE_CONTROLLER);
  esp_now_register_send_cb(OnDataSent);
  esp_now_add_peer(broadcastAddress, ESP_NOW_ROLE_SLAVE, 1, NULL, 0);
}
 
void loop() {
  myData.id = BOARD_ID;
  myData.x = random(1, 50);
  myData.y = random(1, 50);
  myData.z = random(1, 50);
  myData.w = random(1, 50);

  esp_now_send(0, (uint8_t *) &myData, sizeof(myData));
  delay(100);
}

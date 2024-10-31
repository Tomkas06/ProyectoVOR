#include <Arduino.h>

#include <esp_now.h>
#include <WiFi.h>

#include <NewPing.h>

#define TRIGGER_PIN1 4  // Arduino pin tied to trigger pin on the ultrasonic sensor.
#define ECHO_PIN1 5    // Arduino pin tied to echo pin on the ultrasonic sensor.

#define TRIGGER_PIN2  16  // Arduino pin tied to trigger pin on the ultrasonic sensor.
#define ECHO_PIN2     17  // Arduino pin tied to echo pin on the ultrasonic sensor.

#define TRIGGER_PIN3  18  // Arduino pin tied to trigger pin on the ultrasonic sensor.
#define ECHO_PIN3     19 // Arduino pin tied to echo pin on the ultrasonic sensor.

#define TRIGGER_PIN4  21  // Arduino pin tied to trigger pin on the ultrasonic sensor.
#define ECHO_PIN4     22 // Arduino pin tied to echo pin on the ultrasonic sensor.


#define MAX_DISTANCE 50 // Maximum distance we want to ping for (in centimeters). Maximum sensor distance is rated at 400-500cm.
#define MAX_DISTANCEUP 100 // Maximum distance we want to ping for (in centimeters). Maximum sensor distance is rated at 400-500cm.
#define MAX_DISTANCEDN 25 // Maximum distance we want to ping for (in centimeters). Maximum sensor distance is rated at 400-500cm.

NewPing sonarUp(TRIGGER_PIN1, ECHO_PIN1, MAX_DISTANCEUP); // NewPing setup of pins and maximum distance.


NewPing sonarRh(TRIGGER_PIN2, ECHO_PIN2, MAX_DISTANCE); // NewPing setup of pins and maximum distance.

NewPing sonarDn(TRIGGER_PIN3, ECHO_PIN3, MAX_DISTANCEDN); // NewPing setup of pins and maximum distance.

NewPing sonarLh(TRIGGER_PIN4, ECHO_PIN4, MAX_DISTANCE); // NewPing setup of pins and maximum distance.

uint8_t broadcastAddress[] = {0xE0, 0x98, 0x06, 0x99, 0xA2, 0x1C};

typedef struct struct_message {
    int id;
    int x;
    int y;
    int z;
    int w;
} struct_message;

struct_message myData;
esp_now_peer_info_t peerInfo;

bool isDetecUp = false;
bool isDetecRh = false;
bool isDetecDn = false;
bool isDetecLh = false;

int up = 1;
int rh = 0;
int dn = 0;
int lh = 0;

void OnDataSent(const uint8_t *mac_addr, esp_now_send_status_t status) {
  Serial.print("\r\nLast Packet Send Status:\t");
  Serial.println(status == ESP_NOW_SEND_SUCCESS ? "Delivery Success" : "Delivery Fail");
}

void setup() {
  Serial.begin(9600); // Open serial monitor at 115200 baud to see ping results.
  WiFi.mode(WIFI_STA);

  if (esp_now_init() != ESP_OK) {
    Serial.println("Error initializing ESP-NOW");
    return;
  }

  esp_now_register_send_cb(OnDataSent);
  memcpy(peerInfo.peer_addr, broadcastAddress, 6);
  peerInfo.channel = 0;  
  peerInfo.encrypt = false;
  
  if (esp_now_add_peer(&peerInfo) != ESP_OK){
    Serial.println("Failed to add peer");
    return;
  }
}

void loop() {
  
  
  if(sonarUp.ping_cm() != 0){isDetecUp = true;}
  else if(sonarRh.ping_cm() != 0){isDetecRh = true;}
  else if(sonarDn.ping_cm() != 0){isDetecDn = true;}
  else if(sonarLh.ping_cm() != 0){isDetecLh = true;}


  
  if (isDetecUp){up = 0; isDetecUp = false;}
  else{up = 1;}

  if (isDetecRh){rh = 1; isDetecRh = false;}
  else{rh = 0;}

  if (isDetecDn){dn = 1; isDetecDn = false;}
  else{dn = 0;}

  if (isDetecLh){lh = 1; isDetecLh = false;}
  else{lh = 0;}
  

  myData.id = 1;
  myData.x = up;
  myData.y = rh;
  myData.z = dn;
  myData.w = lh;

  esp_err_t result = esp_now_send(broadcastAddress, (uint8_t *) &myData, sizeof(myData));
   
  if (result == ESP_OK) {
    Serial.println("Sent with success");
  }
  else {
    Serial.println("Error sending the data");
  }
  
  
  delay(100);
  
}
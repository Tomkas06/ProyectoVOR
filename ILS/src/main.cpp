#include <Arduino.h>

//Se incluyen las libreria para la comunicacion inalambrica 
#include <esp_now.h>
#include <WiFi.h>
//Este es para controlar el ultrasonico
#include <NewPing.h>

//Se defines los pines para arriba derecha, abajo e izquierda
#define TRIGGER_PIN1 4  
#define ECHO_PIN1 5    

#define TRIGGER_PIN2  16
#define ECHO_PIN2     17

#define TRIGGER_PIN3  18
#define ECHO_PIN3     19

#define TRIGGER_PIN4  21
#define ECHO_PIN4     22

//Distancias maximas, para arriba, abajo y los otros
#define MAX_DISTANCE 50 
#define MAX_DISTANCEUP 150
#define MAX_DISTANCEDN 100

//Se crean los metodos para usar los 4 ultrasonicos
NewPing sonarUp(TRIGGER_PIN1, ECHO_PIN1, MAX_DISTANCEUP);


NewPing sonarRh(TRIGGER_PIN2, ECHO_PIN2, MAX_DISTANCE);

NewPing sonarDn(TRIGGER_PIN3, ECHO_PIN3, MAX_DISTANCEDN);

NewPing sonarLh(TRIGGER_PIN4, ECHO_PIN4, MAX_DISTANCE);

//Se guarda la direccion MAAC o el codigo de la placa receptora
uint8_t broadcastAddress[] = {0xE0, 0x98, 0x06, 0x99, 0xA2, 0x1C};

//Se crea la estructura del mensaje a enviar
typedef struct struct_message {
    int id;
    int x;
    int y;
    int z;
    int w;
} struct_message;

//Honestamente ni idea, los crea
//Ponele
struct_message myData;
esp_now_peer_info_t peerInfo;

//Se establecen que no se detecto ningun objeto
bool isDetecUp = false;
bool isDetecRh = false;
bool isDetecDn = false;
bool isDetecLh = false;

//Variables a enviar
int up = 1;
int rh = 0;
int dn = 0;
int lh = 0;

//Funcion que envia el mensaje
void OnDataSent(const uint8_t *mac_addr, esp_now_send_status_t status) {
  Serial.print("\r\nLast Packet Send Status:\t");
  Serial.println(status == ESP_NOW_SEND_SUCCESS ? "Delivery Success" : "Delivery Fail");
}

void setup() {
  Serial.begin(9600); //Se inicia consola a 9600
  WiFi.mode(WIFI_STA); //Se establece el modo wifi

  //Comprueba si pudo iniciar el modo online
  if (esp_now_init() != ESP_OK) {
    Serial.println("Error initializing ESP-NOW");
    return;
  }

  //Registra la placa receptora
  esp_now_register_send_cb(OnDataSent);
  memcpy(peerInfo.peer_addr, broadcastAddress, 6);
  peerInfo.channel = 0;  
  peerInfo.encrypt = false;
  
  //Indica si se pudo conectar con la placa receptora
  if (esp_now_add_peer(&peerInfo) != ESP_OK){
    Serial.println("Failed to add peer");
    return;
  }
}

void loop() {
  
  //Verifican si hay objetos frente a los sensores, nada mas
  if(sonarUp.ping_cm() != 0){isDetecUp = true;}
  else if(sonarRh.ping_cm() != 0){isDetecRh = true;}
  else if(sonarDn.ping_cm() != 0){isDetecDn = true;}
  else if(sonarLh.ping_cm() != 0){isDetecLh = true;}


  //Verifican que, si hay objetos, envia al receptor cual de todos los sensores tiene un objeto enfrente
  if (isDetecUp){up = 0; isDetecUp = false;}
  else{up = 1;}

  if (isDetecRh){rh = 1; isDetecRh = false;}
  else{rh = 0;}

  if (isDetecDn){dn = 1; isDetecDn = false;}
  else{dn = 0;}

  if (isDetecLh){lh = 1; isDetecLh = false;}
  else{lh = 0;}

  //En caso de que se detecte arriba y abajo al mismo tiempo, se cancelan
  if (isDetecRh && isDetecLh){rh = 0; lh = 0;}
  //Lo mismo
  if (isDetecUp && isDetecDn){up = 0; isDetecDn = 0;}
  
  //Los imprime por consola para verificar que funcionen
  Serial.println(up);
  Serial.println(rh);
  Serial.println(dn);
  Serial.println(lh);

  //Se guardan los valores que se envian
  myData.id = 1;
  myData.x = up;
  myData.y = rh;
  myData.z = dn;
  myData.w = lh;

  //Se envian los valores de los sensores
  esp_err_t result = esp_now_send(broadcastAddress, (uint8_t *) &myData, sizeof(myData));
  
  //Verifica si se pudo enviar correctamente
  if (result == ESP_OK) {
    Serial.println("Sent with success");
  }
  else {
    Serial.println("Error sending the data");
  }
  
  
  delay(100);
  
}
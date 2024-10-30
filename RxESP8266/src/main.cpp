//Se incluyen las librerias de wifi y ESP NOW
#include <ESP8266WiFi.h>
#include <espnow.h>

//Se crea la estructura del mensaje
typedef struct struct_message {
    int id;
    int x;
    int y;
    int z;
    int w;
} struct_message;

//Se usan la estructura del mensaje para los datos de la placa 1 y 2
struct_message myData;
struct_message board1;
struct_message board2;
struct_message boardsStruct[2] = {board1, board2};

//Aqui recibo los datos, creo
void OnDataRecv(uint8_t * mac_addr, uint8_t *incomingData, uint8_t len) {
  memcpy(&myData, incomingData, sizeof(myData));
  boardsStruct[myData.id - 1].x = myData.x;
  boardsStruct[myData.id - 1].y = myData.y;
  boardsStruct[myData.id - 1].z = myData.z;
  boardsStruct[myData.id - 1].w = myData.w;
}

void setup() {
  //Inicio la consola y entro en modo wifi
  Serial.begin(9600);
  WiFi.mode(WIFI_STA);
  WiFi.disconnect();

  //Verifico si inicio o no ESP NOW
  if (esp_now_init() != 0) {
    Serial.println("Error al inicializar ESP-NOW");
    return;
  }

  //Se activa como rol de esclavo, bien negro
  esp_now_set_self_role(ESP_NOW_ROLE_SLAVE);
  esp_now_register_recv_cb(OnDataRecv);
}

void loop(){
  //Se crea la estructura de los mensajes
  int board1X = boardsStruct[0].x;
  int board1Y = boardsStruct[0].y;
  int board1Z = boardsStruct[0].z;
  int board1W = boardsStruct[0].w;
  
  int board2X = boardsStruct[1].x;
  int board2Y = boardsStruct[1].y;
  int board2Z = boardsStruct[1].z;
  
  //Se imprime el mensaje
  Serial.print(board2X); Serial.print(",");
  Serial.print(board2Y); Serial.print(",");
  Serial.print(board2Z); Serial.print(",");

  Serial.print(board1X); Serial.print(",");
  Serial.print(board1Y); Serial.print(",");
  Serial.print(board1Z); Serial.print(",");
  Serial.println(board1W);
  

  delay(100);
}

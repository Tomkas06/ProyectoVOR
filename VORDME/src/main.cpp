//Se añaden las librerias para el modo de comunicacion
#include <ESP8266WiFi.h>
#include <espnow.h>

//Se añaden las librerias para el ultrasonico y el paso a paso
#include <NewPing.h>              // Librería para manejar el sensor ultrasónico
#include <BasicStepperDriver.h>    // Librería para controlar el motor paso a paso

//Se registra el codigo de la placa
uint8_t broadcastAddress[] = {0xE0, 0x98, 0x06, 0x99, 0xA2, 0x1C};
#define BOARD_ID 2

//Se crea la estrucura del mensaje
typedef struct struct_message {
    int id;
    int x;
    int y;
    int z;
    int w;
} struct_message;

struct_message myData;

// Definiciones del motor paso a paso
#define MOTOR_STEPS 200            // Pasos por revolución del motor
#define RPM 120                    // Revoluciones por minuto
#define MICROSTEPS 1               // Modo de microstepping (Full Step)
#define DIR_PIN 5                  // Pin de dirección (D1)
#define STEP_PIN 4                 // Pin de paso (D2)

// Definiciones del sensor ultrasónico
#define TRIGGER_PIN 14             // Pin del trigger del sensor ultrasónico (D5)
#define ECHO_PIN 12                // Pin del echo del sensor ultrasónico (D6)
#define MAX_DISTANCE 50         // Máxima distancia a detectar en cm

// Pin del potenciómetro
#define POT_PIN A0

// Inicialización del motor, sensor y variables
BasicStepperDriver stepper(MOTOR_STEPS, DIR_PIN, STEP_PIN);
NewPing sonar(TRIGGER_PIN, ECHO_PIN, MAX_DISTANCE);

long totalDegrees = 0;            // Suma de los ángulos detectados
int currentAngle = 0;             // Ángulo actual del motor
bool identificado = false;
int distancia = 0;
int distance = 0;                 // Distancia medida por el sensor
int potValue;                 // Valor del potenciómetro
int angle;

//Funcion para enviar el mensaje
void OnDataSent(uint8_t *mac_addr, uint8_t sendStatus) {
  Serial.print("\r\nLast Packet Send Status: ");
  Serial.println(sendStatus == 0 ? "Delivery success" : "Delivery fail");
}

// Función para redondear a múltiplos de 15
int roundToMultipleOf15(int value) {
  return round(value / 15.0) * 15;
}


void setup() {
  Serial.begin(9600);
  WiFi.mode(WIFI_STA);
  WiFi.disconnect();

  //Comprueba si se puedo iniciar el modo de comunicacion inalambrica
  if (esp_now_init() != 0) {
    Serial.println("Error initializing ESP-NOW");
    return;
  } 

  //Verifica si se pudo conectar con la placa receptora
  esp_now_set_self_role(ESP_NOW_ROLE_CONTROLLER);
  esp_now_register_send_cb(OnDataSent);
  esp_now_add_peer(broadcastAddress, ESP_NOW_ROLE_SLAVE, 1, NULL, 0);

  stepper.begin(RPM, MICROSTEPS); // Inicialización del motor paso a paso
}

void loop() {
  for (int i = 0; i < 24; i++) {  // Mueve el motor en incrementos de 15 grados
    currentAngle = i * 15;         // Calcula el ángulo actual
    stepper.rotate(15);              //Mueve el motor 15 grados

    distance = sonar.ping_cm();   // Medir la distancia con el sensor ultrasónico
    potValue = analogRead(POT_PIN); // Leer el valor del potenciómetro
    int mappedValue = map(potValue, 0, 1024, 0, 360); //Mapea el valor del potenciometro
    angle = roundToMultipleOf15(mappedValue); //Lo redondondea

    //Verifica si hay un objeto y si no se habia detectado antes
    if (distance > 0 && identificado == false) { 
        identificado = true;          // Si detecta un objeto
        totalDegrees = currentAngle;
        distancia = distance;
    }

    //Imprime los valores para verificar que todo funcione
    Serial.print(totalDegrees);
    Serial.print(",");
    Serial.print(distancia);
    Serial.print(",");
    Serial.println(angle);

    myData.id = BOARD_ID;
    myData.x = totalDegrees;
    myData.y = distancia;
    myData.z = angle;
    myData.w = 0;

    //Envia los valores
    esp_now_send(0, (uint8_t *) &myData, sizeof(myData));
    delay(100); // Delay de 100 ms
  }

  //Reinicia las variables
  identificado = false;
  totalDegrees = 0;
  distancia = 0;
  
  //A continuacion lo que sigue es lo mismo que arriba solo que en vez de 0 a 360, es de 360 a 0
  // Invertir el movimiento del motor para una vuelta completa en sentido opuesto
  for (int i = 24; i >= 0; i--) {
    currentAngle = i * 15;
    stepper.rotate(-15);  // Movimiento inverso

    distance = sonar.ping_cm();
    potValue = analogRead(POT_PIN); // Leer el valor del potenciómetro
    int mappedValue = map(potValue, 0, 1024, 0, 360);
    angle = roundToMultipleOf15(mappedValue);

    if (distance > 0 && identificado == false) { 
        identificado = true;     
        totalDegrees = currentAngle;
        distancia = distance;
    }

    Serial.print(totalDegrees);
    Serial.print(",");
    Serial.print(distancia);
    Serial.print(",");
    Serial.println(angle);

    myData.id = BOARD_ID;
    myData.x = totalDegrees;
    myData.y = distancia;
    myData.z = angle;
    myData.w = 0;

    esp_now_send(0, (uint8_t *) &myData, sizeof(myData));
    delay(100); // Delay de 100 ms
  }

  identificado = false;
  totalDegrees = 0;
  distancia = 0;
}
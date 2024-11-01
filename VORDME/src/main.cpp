#include <ESP8266WiFi.h>
#include <espnow.h>

#include <NewPing.h>              // Librería para manejar el sensor ultrasónico
#include <BasicStepperDriver.h>    // Librería para controlar el motor paso a paso

//Definiciones del ESPNOW
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

// Definiciones del motor paso a paso
#define MOTOR_STEPS 200            // Pasos por revolución del motor
#define RPM 120                    // Revoluciones por minuto
#define MICROSTEPS 1               // Modo de microstepping (Full Step)
#define DIR_PIN 5                  // Pin de dirección (D1)
#define STEP_PIN 4                 // Pin de paso (D2)

// Definiciones del sensor ultrasónico
#define TRIGGER_PIN 14             // Pin del trigger del sensor ultrasónico (D5)
#define ECHO_PIN 12                // Pin del echo del sensor ultrasónico (D6)
#define MAX_DISTANCE 20         // Máxima distancia a detectar en cm

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

void OnDataSent(uint8_t *mac_addr, uint8_t sendStatus) {
  Serial.print("\r\nLast Packet Send Status: ");
  Serial.println(sendStatus == 0 ? "Delivery success" : "Delivery fail");
}

// Función para redondear a múltiplos de 9
int roundToMultipleOf9(int value) {
  return round(value / 9.0) * 9;
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

  stepper.begin(RPM, MICROSTEPS); // Inicialización del motor paso a paso
}

void loop() {
  for (int i = 0; i < 40; i++) {  // Mueve el motor en incrementos de 9 grados
    currentAngle = i * 9;         // Calcula el ángulo actual
    stepper.move(5);              // Movimiento en Full Step (5 pasos = 9 grados)

    distance = sonar.ping_cm();   // Medir la distancia con el sensor ultrasónico
    potValue = analogRead(POT_PIN); // Leer el valor del potenciómetro
    int mappedValue = map(potValue, 0, 1024, 0, 360);
    angle = roundToMultipleOf9(mappedValue);

    if (distance > 0 && identificado == false) { 
        identificado = true;          // Si detecta un objeto
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

  // Invertir el movimiento del motor para una vuelta completa en sentido opuesto
  for (int i = 40; i >= 0; i--) {
    currentAngle = i * 9;
    stepper.move(-5);  // Movimiento inverso

    distance = sonar.ping_cm();
    potValue = analogRead(POT_PIN); // Leer el valor del potenciómetro
    int mappedValue = map(potValue, 0, 1024, 0, 360);
    angle = roundToMultipleOf9(mappedValue);

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
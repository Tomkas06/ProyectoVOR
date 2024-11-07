#include <NewPing.h>              // Librería para manejar el sensor ultrasónico
#include <BasicStepperDriver.h>    // Librería para controlar el motor paso a paso

// Definiciones del motor paso a paso
#define MOTOR_STEPS 200            // Pasos por revolución del motor
#define RPM 120                    // Revoluciones por minuto
#define MICROSTEPS 1               // Modo de microstepping (Full Step)
#define DIR_PIN 5                  // Pin de dirección
#define STEP_PIN 4                 // Pin de paso

// Definiciones del sensor ultrasónico
#define TRIGGER_PIN 18             // Pin del trigger del sensor ultrasónico
#define ECHO_PIN 19                // Pin del echo del sensor ultrasónico
#define MAX_DISTANCE 20         // Máxima distancia a detectar en cm

// Pin del potenciómetro
#define POT_PIN 34

// Inicialización del motor, sensor y variables
BasicStepperDriver stepper(MOTOR_STEPS, DIR_PIN, STEP_PIN);
NewPing sonar(TRIGGER_PIN, ECHO_PIN, MAX_DISTANCE);

long totalDegrees = 0;            //Grados totales hechos por el motor
int currentAngle = 0;             // Ángulo actual del motor
bool identificado = false;        //Verifica si se detecto un objeto o no
int distancia = 0;                //Guarda la distancia del sensor
int distance = 0;                 // Distancia medida por el sensor (LO MISMO QUE ARRIBA PERO EN ENGLISH)
int potValue;                 // Valor del potenciómetro
int angle;                    //Angulo del potenciometros


// Función para redondear a múltiplos de 9
int roundToMultipleOf9(int value) {
  return round(value / 9.0) * 9;
}


void setup() {
  Serial.begin(115200);
  stepper.begin(RPM, MICROSTEPS); // Inicialización del motor paso a paso
}

/*
A partir de aqui para abajo no me importo comentar
Entren a VOR/DME y ahi esta
no me voy a disculpar porque es una banda
quiero hacer otra cosa ademas
...
...
...
...
Bueno, a seguir trabajando
*/

void loop() {
  for (int i = 0; i < 40; i++) {  // Mueve el motor en incrementos de 9 grados
    currentAngle = i * 9;         // Calcula el ángulo actual
    stepper.move(5);              // Movimiento en Full Step (5 pasos = 9 grados)

    distance = sonar.ping_cm();   // Medir la distancia con el sensor ultrasónico
    potValue = analogRead(POT_PIN); // Leer el valor del potenciómetro
    int mappedValue = map(potValue, 0, 4095, 0, 360);
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
    int mappedValue = map(potValue, 0, 4095, 0, 360);
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
    delay(100); // Delay de 100 ms
  }

  identificado = false;
  totalDegrees = 0;
  distancia = 0;
}


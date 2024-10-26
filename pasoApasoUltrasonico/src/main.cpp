#include <NewPing.h>              // Librería para manejar el sensor ultrasónico
#include <BasicStepperDriver.h>    // Librería para controlar el motor paso a paso

// Definiciones del motor paso a paso
#define MOTOR_STEPS 200            // Pasos por revolución del motor
#define RPM 120                    // Revoluciones por minuto
#define MICROSTEPS 1               // Modo de microstepping (Full Step)
#define DIR_PIN 4                  // Pin de dirección
#define STEP_PIN 5                 // Pin de paso

// Definiciones del sensor ultrasónico
#define TRIGGER_PIN 18             // Pin del trigger del sensor ultrasónico
#define ECHO_PIN 19                // Pin del echo del sensor ultrasónico
#define MAX_DISTANCE 20         // Máxima distancia a detectar en cm

// Pin del potenciómetro
#define POT_PIN 34

// Inicialización del motor, sensor y variables
BasicStepperDriver stepper(MOTOR_STEPS, DIR_PIN, STEP_PIN);
NewPing sonar(TRIGGER_PIN, ECHO_PIN, MAX_DISTANCE);

long totalDegrees = 0;            // Suma de los ángulos detectados
int sampleCount = 0;              // Número de muestras tomadas para el promedio
int currentAngle = 0;             // Ángulo actual del motor
int previousAngle = -1;           // Ángulo anterior del motor
int distance = 0;                 // Distancia medida por el sensor
int potValue = 0;                 // Valor del potenciómetro


// Función para redondear a múltiplos de 9
int roundToMultipleOf9(int value) {
  return round(value / 9.0) * 9;
}


void setup() {
  Serial.begin(115200);
  stepper.begin(RPM, MICROSTEPS); // Inicialización del motor paso a paso
}

void loop() {
  for (int i = 0; i < 40; i++) {  // Mueve el motor en incrementos de 9 grados
    currentAngle = i * 9;         // Calcula el ángulo actual
    stepper.move(5);              // Movimiento en Full Step (5 pasos = 9 grados)

    distance = sonar.ping_cm();   // Medir la distancia con el sensor ultrasónico
    potValue = 180; // Leer el valor del potenciómetro

    if (distance > 0) {           // Si detecta un objeto
      totalDegrees += currentAngle;
      sampleCount++;

      if (currentAngle != previousAngle) {
        int averageAngle = roundToMultipleOf9(totalDegrees / sampleCount);
        // Imprime los valores juntos: ángulo promedio, distancia, valor del potenciómetro
        Serial.print(averageAngle);
        Serial.print(",");
        Serial.print(distance);
        Serial.print(",");
        Serial.println(potValue);
      }
    } else {                      // Si no detecta el objeto, reinicia las variables
      totalDegrees = 0;
      sampleCount = 0;
    }

    previousAngle = currentAngle;
    delay(100); // Delay de 100 ms
  }

  // Invertir el movimiento del motor para una vuelta completa en sentido opuesto
  for (int i = 39; i >= 0; i--) {
    currentAngle = i * 9;
    stepper.move(-5);  // Movimiento inverso

    distance = sonar.ping_cm();
    potValue = 180;

    if (distance > 0) {
      totalDegrees += currentAngle;
      sampleCount++;

      if (currentAngle != previousAngle) {
        int averageAngle = roundToMultipleOf9(totalDegrees / sampleCount);
        Serial.print(averageAngle);
        Serial.print(",");
        Serial.print(distance);
        Serial.print(",");
        Serial.println(potValue);
      }
    } else {
      totalDegrees = 0;
      sampleCount = 0;
    }

    previousAngle = currentAngle;
    delay(100); // Delay de 100 ms
  }
}


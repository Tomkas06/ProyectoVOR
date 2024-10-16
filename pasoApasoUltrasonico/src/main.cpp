#include <Arduino.h>
#include <NewPing.h>        // Librería para manejar el sensor ultrasónico
#include <BasicStepperDriver.h>  // Librería para controlar el motor paso a paso

// Definiciones del motor paso a paso
#define MOTOR_STEPS 200         // Pasos por revolución del motor (usualmente 200)
#define RPM 120                 // Revoluciones por minuto
#define MICROSTEPS 1            // Modo de microstepping (1=full step, 2=half step, etc.)
#define DIR_PIN 5               // Pin de dirección para el A4988
#define STEP_PIN 4              // Pin de paso para el A4988

// Definiciones del sensor ultrasónico
#define TRIGGER_PIN 12          // Pin del trigger (disparo) del sensor ultrasónico
#define ECHO_PIN 11             // Pin del echo (respuesta) del sensor ultrasónico
#define MAX_DISTANCE 200        // Máxima distancia a detectar en cm

// Inicialización del motor y del sensor
BasicStepperDriver stepper(MOTOR_STEPS, DIR_PIN, STEP_PIN);
NewPing sonar(TRIGGER_PIN, ECHO_PIN, MAX_DISTANCE);

// Variables para manejar el promedio de ángulos y detección
long totalDegrees = 0;          // Suma de los ángulos detectados
int sampleCount = 0;            // Número de muestras tomadas para el promedio
int currentAngle = 0;           // Ángulo actual del motor
int previousAngle = -1;         // Ángulo anterior del motor
int distance = 0;               // Distancia medida por el sensor

void setup() {
  Serial.begin(115200);
  stepper.begin(RPM, MICROSTEPS);  // Inicialización del motor paso a paso
}

int roundToMultipleOf9(int value) {
  return round(value / 9.0) * 9;
}

void loop() {
  for (int i = 0; i < 40; i++) {   // Mueve el motor paso a paso en incrementos de 9 grados (360/9 = 40 pasos)
    currentAngle = i * 9;          // Calcula el ángulo actual
    stepper.move(50);              // Movimiento en pasos (50 pasos = 9 grados para un motor de 200 pasos/rev)

    // Medir la distancia con el sensor ultrasónico
    distance = sonar.ping_cm();
    
    if (distance > 0) {            // Si detecta un objeto
      totalDegrees += currentAngle;
      sampleCount++;

      // Si hay cambio en el ángulo, imprime los valores promedio
      if (currentAngle != previousAngle) {
        int averageAngle = roundToMultipleOf9(totalDegrees / sampleCount);
        Serial.print(averageAngle);
        Serial.print(",");
        Serial.println(distance);
      }
    } else {  // Si no se detecta el objeto, reiniciar variables
      totalDegrees = 0;
      sampleCount = 0;
    }

    previousAngle = currentAngle;
    delay(100); // Pequeña pausa para estabilizar el sistema
  }

  // Invertir el movimiento del motor para una vuelta completa en sentido opuesto
  for (int i = 39; i >= 0; i--) {
    currentAngle = i * 9;
    stepper.move(-50);  // Movimiento inverso

    distance = sonar.ping_cm();
    
    if (distance > 0) {
      totalDegrees += currentAngle;
      sampleCount++;

      if (currentAngle != previousAngle) {
        int averageAngle = roundToMultipleOf9(totalDegrees / sampleCount);
        Serial.print(averageAngle);
        Serial.print(",");
        Serial.println(distance);
      }
    } else {
      totalDegrees = 0;
      sampleCount = 0;
    }

    previousAngle = currentAngle;
    delay(100); // Pausa
  }
}

// Función para redondear a múltiplos de 9


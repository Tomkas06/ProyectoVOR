#include <Arduino.h>
#include "BasicStepperDriver.h"

#define MOTOR_STEPS 200  // Pasos por revolución (200 pasos = 1.8° por paso)
#define RPM 120
#define MICROSTEPS 1

#define DIR_PIN 5
#define STEP_PIN 4

BasicStepperDriver stepper(MOTOR_STEPS, DIR_PIN, STEP_PIN);

int stepCount = 0;  // Contador de pasos
int totalSteps = 200;  // Pasos para una vuelta completa

// Variable para almacenar el ángulo en grados
float currentAngle = 0;

void setup() {
    stepper.begin(RPM, MICROSTEPS);
    Serial.begin(115200);  // Inicia la comunicación con el Monitor Serial
}

void loop() {
    // Mover en incrementos de 9 grados (5 pasos)
    if (stepCount < totalSteps) {
        stepper.move(5);  // Mover 5 pasos = 9 grados
        stepCount += 5;   // Aumenta el contador de pasos
        currentAngle = stepCount * 1.8;  // Calcula el ángulo actual
    } 
    // Cuando ha completado una vuelta completa, moverse en sentido opuesto
    else if (stepCount >= totalSteps && stepCount < totalSteps * 2) {
        stepper.move(-5);  // Mover en sentido inverso 5 pasos = 9 grados hacia atrás
        stepCount += 5;    // Contador sigue aumentando en pasos negativos
        currentAngle = 360 - (stepCount - totalSteps) * 1.8;  // Calcula el ángulo en reversa
    } 
    
    // Si ya ha hecho 360 grados en ambos sentidos, reinicia el ciclo
    if (stepCount >= totalSteps * 2) {
        stepCount = 0;  // Reinicia el conteo de pasos
        delay(2000);    // Pausa de 2 segundos
    }

    // Imprime el ángulo actual en el Monitor Serial
    Serial.println(currentAngle);
    
    delay(500);  // Pausa entre movimientos
}

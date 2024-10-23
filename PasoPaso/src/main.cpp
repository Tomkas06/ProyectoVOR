#include <Arduino.h>
#include <BasicStepperDriver.h>  // Incluir la librería StepperDriver

// Definir los parámetros del motor paso a paso
#define MOTOR_STEPS 200   // Pasos por revolución del motor (usualmente 200)
#define RPM 60            // Velocidad del motor en RPM
#define DIR_PIN 5         // Pin de dirección
#define STEP_PIN 4        // Pin de paso

// Crear una instancia del controlador del motor
BasicStepperDriver stepper(MOTOR_STEPS, DIR_PIN, STEP_PIN);

void setup() {
  // Inicializar el motor con la velocidad y el modo de microstepping deseado
  stepper.begin(RPM, 1);  // 1 = modo de paso completo (full step)

  Serial.begin(115200);
  Serial.println("Iniciando motor paso a paso...");
}

void loop() {
  // Hacer una revolución completa en el sentido horario
  Serial.println("Rotando 360 grados en sentido horario...");
  stepper.rotate(360);  // Gira 360 grados

  delay(2000);  // Esperar 2 segundos

  // Hacer una revolución completa en el sentido antihorario
  Serial.println("Rotando 360 grados en sentido antihorario...");
  stepper.rotate(-360);  // Gira 360 grados en el sentido inverso

  delay(2000);  // Esperar 2 segundos
}

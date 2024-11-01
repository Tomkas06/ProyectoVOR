#include <BasicStepperDriver.h>

// Configuración para el motor y el driver TB6600
#define MOTOR_STEPS 200   // Número de pasos por vuelta completa del motor
#define DIR_PIN 5         // Pin de dirección del TB6600
#define STEP_PIN 4        // Pin de paso del TB6600
#define RPM 120           // Velocidad en revoluciones por minuto
#define MICROSTEPS 1      // Modo de microstepping (1 = paso completo)

BasicStepperDriver stepper(MOTOR_STEPS, DIR_PIN, STEP_PIN);

void setup() {
    Serial.begin(9600);
    stepper.begin(RPM, MICROSTEPS);  // Inicializa el motor a la velocidad y modo de paso completo
}

void loop() {
    stepper.rotate(9); 

    delay(1000);                         // Pausa antes de repetir
}

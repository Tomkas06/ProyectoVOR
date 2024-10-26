#include <BasicStepperDriver.h>

// Configuración para el motor y el driver TB6600
#define MOTOR_STEPS 200   // Número de pasos por vuelta completa del motor
#define DIR_PIN 4         // Pin de dirección del TB6600
#define STEP_PIN 5        // Pin de paso del TB6600
#define RPM 120           // Velocidad en revoluciones por minuto
#define MICROSTEPS 1      // Modo de microstepping (1 = paso completo)

BasicStepperDriver stepper(MOTOR_STEPS, DIR_PIN, STEP_PIN);

void setup() {
    Serial.begin(115200);
    stepper.begin(RPM, MICROSTEPS);  // Inicializa el motor a la velocidad y modo de paso completo
}

void loop() {
    for (int i = 0; i < 40; i++) {      // 40 veces para completar una vuelta de 360 grados
        stepper.rotate(9);              // Rota 9 grados en sentido horario
        delay(500);                     // Pausa de medio segundo entre pasos (ajústala según tus necesidades)
    }

    delay(1000);                         // Pausa de un segundo después de completar una vuelta

    for (int i = 0; i < 40; i++) {      // 40 veces en sentido opuesto para completar una vuelta en sentido antihorario
        stepper.rotate(-9);             // Rota 9 grados en sentido antihorario
        delay(500);                     // Pausa de medio segundo entre pasos
    }

    delay(1000);                         // Pausa antes de repetir
}

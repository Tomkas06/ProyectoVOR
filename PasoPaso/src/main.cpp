//Se añade la libreria para controlar el motor paso a paso
#include <BasicStepperDriver.h>

//Se definen las configuraciones del paso a paso
//Numero de pasos, pines, rpm, tipo de paso
#define MOTOR_STEPS 200   // Número de pasos por vuelta completa del motor
#define DIR_PIN 5         // Pin de dirección del TB6600
#define STEP_PIN 4        // Pin de paso del TB6600
#define RPM 120           // Velocidad en revoluciones por minuto
#define MICROSTEPS 1      // Modo de microstepping (1 = paso completo)

//Se crea el paso a paso
BasicStepperDriver stepper(MOTOR_STEPS, DIR_PIN, STEP_PIN);


void setup() {
    //Se inicia consola a 9600
    Serial.begin(9600);
    //Inicializa el motor a la velocidad y modo de paso completo
    stepper.begin(RPM, MICROSTEPS);  
}

void loop() {
    //Rota el paso a paso 24 veces cada 15 grados
    for (int i = 0; i< 24; i++){
        Serial.println(i*15);
        //Rota el motor 15 grados
        stepper.rotate(15); 
        // Pausa antes de repetir
        delay(100);                         
    }


}

//Se incluye la libreria para controlar el ultrasonico
#include <NewPing.h>

//Se definen los pines del ultrasonico
#define TRIGGER_PIN1  14  // Trigger es el que envia el sonido (D5)
#define ECHO_PIN1     12  // Echo es el que escuha el sonido(D6)

#define MAX_DISTANCE 100 //Se establece la distancia maxima del sensor

NewPing sonar(TRIGGER_PIN1, ECHO_PIN1, MAX_DISTANCE); //Se configura el ultrasonico

void setup() {
  Serial.begin(9600); //Abre monitor serie a 9600 (baudios)
}

void loop() {
  //Imprime por consola la distancia del sensor al objeto
  Serial.println(sonar.ping_cm());
  delay(1000);
}
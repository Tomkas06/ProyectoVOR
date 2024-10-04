/*
	Capitulo 69 de Arduino desde cero en Ingles.
	Simple programa para controlar un motor del tipo bipolar NEMA 17 mediante el
	controlador driver A4988 logrando un giro de media vuelta en un sentido y en otro

	Autor: Yo

*/
#include <Arduino.h>

#define STEP 4			// pin STEP de A4988 a pin 4
#define DIR 5			// pin DIR de A4988 a pin 5

void setup() 
{
  pinMode(STEP, OUTPUT);	// pin 4 como salida
  pinMode(DIR, OUTPUT);		// pin 5 como salida
}

void loop() 
{
  digitalWrite(DIR, HIGH);		// giro en un sentido
  for(int i = 0; i < 200; i++){   	// 200 pasos para motor de 1.80 grados de angulo de paso
    digitalWrite(STEP, HIGH);     	// nivel alto
    delay(10);			  	// por 10 mseg
    digitalWrite(STEP, LOW);      	// nivel bajo
    delay(10);			  	// por 10 mseg
  }

  

  
  //delay(1000);			  	// demora de 2 segundos
}
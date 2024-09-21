#include <Arduino.h>

int potPin = 34;   // Pin donde está conectado el potenciómetro
int potValue;      // Variable para almacenar el valor del potenciómetro
int angle;         // Variable para almacenar el ángulo del potenciómetro
int randomAngle;   // Variable para almacenar el valor aleatorio múltiplo de 9

void setup() {
  Serial.begin(115200);
  randomAngle = (random(0, 40)) * 9;  // random(0, 40) genera números entre 0 y 39, por lo que multiplicar por 9 da valores divisibles por 9
}

void loop() {
  // Leer el valor del potenciómetro y mapear a un rango de 0 a 360
  potValue = analogRead(potPin);            
  int mappedValue = map(potValue, 0, 4095, 0, 360); 
  angle = (mappedValue / 9) * 9;  // Redondear al múltiplo de 9 más cercano

  // Generar un número aleatorio entre 0 y 360 divisible por 9
  

  // Enviar ambos valores a Processing separados por una coma
  Serial.print(angle);    
  Serial.print(",");
  Serial.println(randomAngle);

  delay(100); // Pausa para evitar demasiadas lecturas rápidas
}

#include <Arduino.h>
int potPin = 34;   // Pin donde está conectado el potenciómetro
int potValue;      // Variable para almacenar el valor del potenciómetro
int angle;         // Variable para almacenar el ángulo del círculo

void setup() {
  Serial.begin(115200);
}

void loop() {
  potValue = analogRead(potPin);            // Leer el valor del potenciómetro
  int mappedValue = map(potValue, 0, 4095, 0, 360); // Mapear a rango 0-360
  angle = (mappedValue / 9) * 9;            // Redondear al múltiplo de 9 más cercano
  
  //Serial.print("Potentiometer Value: ");
  //Serial.print(potValue);
  //Serial.print(" | Angle: ");
  Serial.println(angle); // Mostrar el ángulo calculado
  
  delay(100); // Pausa para evitar demasiadas lecturas rápidas
}

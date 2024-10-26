#include <Arduino.h>

int potPin = 34;   // Pin donde está conectado el potenciómetro
int potValue;      // Variable para almacenar el valor del potenciómetro
int angle;         // Variable para almacenar el ángulo del potenciómetro
void setup() {
  Serial.begin(115200);
}

void loop() {
  // Leer el valor del potenciómetro y mapear a un rango de 0 a 360
  potValue = analogRead(potPin);            
  int mappedValue = map(potValue, 0, 4095, 0, 360); 
  angle = (mappedValue / 9) * 9;  // Redondear al múltiplo de 9 más cercano
  
  // Enviar ambos valores a Processing separados por una coma
  Serial.print(angle);    
  delay(100); // Pausa para evitar demasiadas lecturas rápidas
}

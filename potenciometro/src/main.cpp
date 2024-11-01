#include <Arduino.h>

int potPin = A0;   // Pin donde está conectado el potenciómetro
int potValue;      // Variable para almacenar el valor del potenciómetro
int angle;         // Variable para almacenar el ángulo del potenciómetro
void setup() {
  Serial.begin(9600);
}

void loop() {
  // Leer el valor del potenciómetro y mapear a un rango de 0 a 360
  potValue = analogRead(potPin);   
  Serial.print("El analogo es: ");
  Serial.println(potValue);
           
  int mappedValue = map(potValue, 0, 1024, 0, 360); 
  angle = (mappedValue / 9) * 9;  // Redondear al múltiplo de 9 más cercano
  
  // Enviar ambos valores a Processing separados por una coma
  Serial.print("El angulo es: ");    
  Serial.println(angle);    
  delay(100); // Pausa para evitar demasiadas lecturas rápidas
}

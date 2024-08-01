#include <NewPing.h>

#define TRIGGER_PIN  16  // Arduino pin tied to trigger pin on the ultrasonic sensor.
#define ECHO_PIN     17  // Arduino pin tied to echo pin on the ultrasonic sensor.
#define MAX_DISTANCE 180 // Maximum distance we want to ping for (in centimeters). Maximum sensor distance is rated at 400-500cm.

NewPing sonar(TRIGGER_PIN, ECHO_PIN, MAX_DISTANCE); // NewPing setup of pins and maximum distance.

void setup() {
  Serial.begin(115200); // Open serial monitor at 115200 baud to see ping results.
}

void loop() {
  for(int i = 0; i<=360; i++){
    if (sonar.ping_cm() == 0){
      Serial.println("--Fuera de rango--");
    }else{
      Serial.println(sonar.ping_cm()); // Send ping, get distance in cm and print result (0 = outside set distance range)
    }
    delay(30);  
  }
  Serial.println(millis());
}
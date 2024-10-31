#include <NewPing.h>

#define TRIGGER_PIN1  14  // D5
#define ECHO_PIN1     12  // D6

#define MAX_DISTANCE 100 // Maximum distance we want to ping for (in centimeters). Maximum sensor distance is rated at 400-500cm.

NewPing sonar(TRIGGER_PIN1, ECHO_PIN1, MAX_DISTANCE); // NewPing setup of pins and maximum distance.

void setup() {
  Serial.begin(9600); // Open serial monitor at 115200 baud to see ping results.
}

void loop() {

  Serial.println(sonar.ping_cm());
  delay(1000);
}
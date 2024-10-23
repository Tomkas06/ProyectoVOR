#include <NewPing.h>

#define TRIGGER_PIN1  4  // Arduino pin tied to trigger pin on the ultrasonic sensor.
#define ECHO_PIN1     5  // Arduino pin tied to echo pin on the ultrasonic sensor.

#define MAX_DISTANCE 180 // Maximum distance we want to ping for (in centimeters). Maximum sensor distance is rated at 400-500cm.

NewPing sonar1(TRIGGER_PIN1, ECHO_PIN1, MAX_DISTANCE); // NewPing setup of pins and maximum distance.

void setup() {
  Serial.begin(115200); // Open serial monitor at 115200 baud to see ping results.
}

void loop() {

  Serial.println(sonar1.ping_cm());
  Serial.println("Sonico 1");
  delay(1000);
}
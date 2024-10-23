#include <Arduino.h>
#include <NewPing.h>

#define TRIGGER_PIN1  1  // Arduino pin tied to trigger pin on the ultrasonic sensor.
#define ECHO_PIN1     2  // Arduino pin tied to echo pin on the ultrasonic sensor.

#define TRIGGER_PIN2  3  // Arduino pin tied to trigger pin on the ultrasonic sensor.
#define ECHO_PIN2     4  // Arduino pin tied to echo pin on the ultrasonic sensor.

#define TRIGGER_PIN3  5  // Arduino pin tied to trigger pin on the ultrasonic sensor.
#define ECHO_PIN3     6  // Arduino pin tied to echo pin on the ultrasonic sensor.

#define TRIGGER_PIN4  7  // Arduino pin tied to trigger pin on the ultrasonic sensor.
#define ECHO_PIN4     8  // Arduino pin tied to echo pin on the ultrasonic sensor.


#define MAX_DISTANCE 100 // Maximum distance we want to ping for (in centimeters). Maximum sensor distance is rated at 400-500cm.

NewPing sonarUp(TRIGGER_PIN1, ECHO_PIN1, MAX_DISTANCE); // NewPing setup of pins and maximum distance.

NewPing sonarRh(TRIGGER_PIN2, ECHO_PIN2, MAX_DISTANCE); // NewPing setup of pins and maximum distance.

NewPing sonarDn(TRIGGER_PIN3, ECHO_PIN3, MAX_DISTANCE); // NewPing setup of pins and maximum distance.

NewPing sonarLh(TRIGGER_PIN4, ECHO_PIN4, MAX_DISTANCE); // NewPing setup of pins and maximum distance.

bool isDetecUp = false;
bool isDetecRh = false;
bool isDetecDn = false;
bool isDetecLh = false;

String enviar[4];
String result = "";

void setup() {
  Serial.begin(9600); // Open serial monitor at 115200 baud to see ping results.
}

void loop() {

  if(sonarUp.ping_cm() != 0){isDetecUp = true;}
  else if(sonarRh.ping_cm() != 0){isDetecRh = true;}
  else if(sonarDn.ping_cm() != 0){isDetecDn = true;}
  else if(sonarLh.ping_cm() != 0){isDetecLh = true;}

  if (isDetecUp){enviar[0] = 1;}
  else{enviar[0] = 0;}

  if (isDetecRh){enviar[1] = 1;}
  else{enviar[1] = 0;}

  if (isDetecDn){enviar[2] = 1;}
  else{enviar[2] = 0;}

  if (isDetecLh){enviar[3] = 1;}
  else{enviar[3] = 0;}

  for (int i = 0; i < 4; i++) {
    result += enviar[i];  // Concatenar cada string
  }

  Serial.println(result);
  
}
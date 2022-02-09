// ProCodeCG Kids Arduino Handout 7.0 - Ultrasonic sensor

#include <NewPing.h>

#define TRIG 11
#define ECHO 12
#define BUZZER 10
#define MAX_DIST 110

NewPing sonar(TRIG, ECHO, MAX_DIST);

void setup() {
  Serial.begin(9600);

  pinMode(BUZZER, OUTPUT);
}

void loop() {
  delay(60);
  unsigned int cm = sonar.ping_cm();
  if (cm <= 100 && cm != 0) digitalWrite(BUZZER, HIGH);
  else digitalWrite(BUZZER, LOW);
}

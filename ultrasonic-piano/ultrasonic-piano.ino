// ProCodeCG Kids Arduino Handout 7.0 - Ultrasonic Piano

#define TRIG 11
#define ECHO 12
#define BUZZER 10

int sound = 250;

void setup() {
  Serial.begin(9600);
  pinMode(TRIG, OUTPUT);
  pinMode(ECHO, INPUT);
  pinMode(BUZZER, OUTPUT);
}

void loop() {
  digitalWrite(TRIG, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG, LOW);
  int dur = pulseIn(ECHO, HIGH);
  int dist = (dur/2) / 29;

  if (dist <= 40) sound = 528;
  if (dist < 35)  sound = 495;
  if (dist < 30)  sound = 440;
  if (dist < 25)  sound = 396;
  if (dist < 20)  sound = 352;
  if (dist < 15)  sound = 330;
  if (dist < 10)  sound = 297;
  if (dist < 5)   sound = 262;

  if (dist > 40 || dist <= 0) {
    Serial.println("Out of range");
    noTone(BUZZER);
  } else {
    Serial.print(dist);
    Serial.println(" cm");
    tone(BUZZER, sound);
  }

  delay(500);
}

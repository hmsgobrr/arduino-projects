// https://arduinogetstarted.com/tutorials/arduino-button-led
#define BUTTON_PIN 4
#define LED_PIN 6

void setup() {
  pinMode(LED_PIN, OUTPUT);
  pinMode(BUTTON_PIN, INPUT_PULLUP);
}

void loop() {
  digitalWrite(LED_PIN, digitalRead(BUTTON_PIN) == LOW ? HIGH : LOW);
}

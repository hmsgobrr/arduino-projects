#include <Wire.h>
#include <Adafruit_SSD1306.h>

#include "Game.h"

#define SWIDTH 128
#define SHEIGHT 64

#define OLED_RESET -1
#define SCREEN_ADDRESS 0x3C
Adafruit_SSD1306 scr(SWIDTH, SHEIGHT, &Wire, OLED_RESET);

// #define BUTTON A2

void setup() {
  Serial.begin(9600);

  if(!scr.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)) {
    Serial.println(F("SSD1306 allocation failed"));
    for(;;);
  }

  // pinMode(BUTTON, INPUT);
  // digitalWrite(BUTTON, HIGH);

  Game::init();
}

void loop() {
  scr.clearDisplay();

  // display.drawRect(0, 0, 128, 64, 1);
  // display.drawRect(1, 1, 126, 62, 1);

  Game::tick(scr);

  scr.display();
  delay(30);
}

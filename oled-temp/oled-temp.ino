#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <dht.h>

#define DHT11_PIN A0

#define SWIDTH 128
#define SHEIGHT 64

Adafruit_SSD1306 oled(SWIDTH, SHEIGHT, &Wire, -1);
dht DHT;

void setup() {
  Serial.begin(9600);

  if (!oled.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println(F("SSD1306 allocation failed"));
    while (true);
  }

  delay(2000);
}

void loop() {
  oled.clearDisplay();

  oled.setTextSize(1);
  oled.setTextColor(WHITE);
  oled.setCursor(0, 0);
  DHT.read11(DHT11_PIN);
  char text[50];
  sprintf(text, "Temperature = %d\nHumidity = %d", (int)DHT.temperature, (int)DHT.humidity);
  oled.println(text);
  
  oled.display();

  delay(2000);
}

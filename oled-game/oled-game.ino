#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define JOY_X_PIN  A0
#define JOY_Y_PIN  A1
#define BUTTON_PIN A3

#define SWIDTH 128
#define SHEIGHT 64

#define PLAYER_Y 55
#define PLAYER_SPEED 3
#define PLAYER_SIZE 3

#define TARGET_MIN_X 5
#define TARGET_MIN_Y 5
#define TARGET_MAX_X (SWIDTH-5)
#define TARGET_MAX_Y 35
#define TARGET_SIZE 3

#define BULLET_SPEED 5
#define BULLET_SIZE 1
#define MAX_BULLET 30

struct Bullet {
  int x, y;
  bool active{false};

  void update() {
    y -= BULLET_SPEED;
    if (y < 0) active = false;
  }

  void draw(Adafruit_SSD1306& oled) {
    oled.fillCircle(x, y, BULLET_SIZE, WHITE);
  }
};

Adafruit_SSD1306 oled(SWIDTH, SHEIGHT, &Wire, -1);

Bullet bulletPool[MAX_BULLET];

Bullet* getBullet() {
  for (int i = 0; i < MAX_BULLET; i++) {
    if (!bulletPool[i].active) return &bulletPool[i];
  }

  return nullptr;
}

bool checkCircleColl(int x1, int y1, int r1, int x2, int y2, int r2) {
  return sqrt(pow((x2 - x1), 2) + pow((y2 - y1), 2)) < (r1 + r2);
}

int px;
int tx, ty;
bool canShoot = true;

int score = 0;

void setup() {
  Serial.begin(9600);
  randomSeed(analogRead(0));

  if (!oled.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println(F("SSD1306 allocation failed"));
    while (true);
  }

  pinMode(BUTTON_PIN, INPUT_PULLUP);

  delay(2000);

  px = 64;
  tx = random(TARGET_MIN_X, TARGET_MAX_X);
  ty = random(TARGET_MIN_Y, TARGET_MAX_Y);
}

void loop() {
  // Serial.print(analogRead(JOY_X_PIN));
  // Serial.print("\t");
  // Serial.println(analogRead(JOY_Y_PIN));

  if (analogRead(JOY_X_PIN) > 750) px += PLAYER_SPEED;
  else if (analogRead(JOY_X_PIN) < 250) px -= PLAYER_SPEED;

  if (px < 0) px = 0;
  if (px > SWIDTH) px = SWIDTH;

  if (digitalRead(BUTTON_PIN) == LOW && canShoot) {
    Bullet* bullet = getBullet();
    if (bullet) {
      bullet->active = true;
      bullet->x = px;
      bullet->y = PLAYER_Y;
    }
    canShoot = false;
  } else if (digitalRead(BUTTON_PIN) == HIGH && !canShoot) {
    canShoot = true;
  }

  oled.clearDisplay();

  for (Bullet& bullet : bulletPool) {
    if (bullet.active) {
      if (checkCircleColl(bullet.x, bullet.y, BULLET_SIZE, tx, ty, TARGET_SIZE)) {
        bullet.active = false;
        tx = random(TARGET_MIN_X, TARGET_MAX_X);
        ty = random(TARGET_MIN_Y, TARGET_MAX_Y);
        score++;
        continue;
      }

      bullet.update();
      bullet.draw(oled);
    }
  }

  oled.drawCircle(px, PLAYER_Y, PLAYER_SIZE, WHITE);
  oled.fillCircle(tx, ty, TARGET_SIZE, WHITE);

  char scoreText[12];
  sprintf(scoreText, "SCORE: %d", score);
  oled.setTextSize(1);
  oled.setTextColor(WHITE);
  oled.setCursor(5, 5);
  oled.println(scoreText);

  oled.display();
}
